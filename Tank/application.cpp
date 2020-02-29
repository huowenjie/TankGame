#include <cstdlib>
#include <vector>
#include <sdl2/SDL.h>

#undef __gl_h_
#include <glad/glad.h>

#include "application.h"
#include "app-debug.h"
#include "shader.h"
#include "game.h"

namespace hwj 
{
	Application::Application() : 
		mainWindow(nullptr),
		mainContext(nullptr),
		winWidth(800), 
		winHeight(600),
		defRenderFps(60),
		defLogicFps(30)
	{
	}
	
	Application::Application(int width, int height) :
		winWidth(width), winHeight(height)
	{
	}

	Application::~Application() 
	{
		if (mainContext != nullptr) {
			SDL_GL_DeleteContext(mainContext);
		}

		if (mainWindow != NULL) {
			SDL_DestroyWindow((SDL_Window *)mainWindow);
			mainWindow = NULL;
		}

		SDL_Quit();
	}

	void Application::CreateWindow(const char *title)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			LOG_INFO("Init Failed!\n");
			std::abort();
		}

		// 使用 opengl 4.5
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_Window *window = SDL_CreateWindow(
			title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			winWidth, winHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (!window) {
			LOG_INFO("Failed to create GLFW window\n");
			std::abort();
		}

		// 创建 opengl 上下文对象
		SDL_GLContext context = SDL_GL_CreateContext(window);

		if (!context) {
			LOG_INFO("Failed to create OpenGl context\n");
			std::abort();
		}

		mainWindow = window;
		mainContext = context;
	}

	void Application::LoadGraphicApi() 
	{
		// 初始化 glad
		if (!gladLoadGL()) {
			LOG_INFO("Failed to initialize GLAD\n");
			std::abort();
		}
	}

	void Application::Render() 
	{
		if (!mainWindow) {
			return;
		}

		ShaderProgram shader;

		shader.LoadShaderFile("triangle.vert", "triangle.frag");
		shader.UseProgram();
		mGame.StartGame();

		// 设置投影矩阵，将 800*600 的窗口元素投影到 opengl -1，1 的范围
		glm::mat4 projection = 
			glm::ortho(0.0f, (float)winWidth, 0.0f, (float)winHeight, -1.0f, 1.0f);
		shader.SetMat4f("projection", &projection[0][0]);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// 主循环
		Uint32 logicDelt = 1000 / defLogicFps;
		Uint32 rendDelt  = 1000 / defRenderFps;
		Uint32 curTime   = SDL_GetTicks();

		Uint32 logicCount = 0;		// 逻辑贞计时器
		Uint32 newTime    = 0;		// 每帧开启时的时间
		Uint32 frameTime  = 0;		// 每个渲染帧所用的时间
		Uint32 frameLose  = 250;	// 最大掉帧时间 ms
		float interpAlpha = 0.0f;	// 当前帧的插值比率

		SDL_Event sdlEvent;
		SDL_Window *window = reinterpret_cast<SDL_Window *>(mainWindow);

		while (mGame.IsRunning()) {
			while (SDL_PollEvent(&sdlEvent) != 0) {
				if (sdlEvent.type == SDL_QUIT)
				{
					mGame.StopGame();
				}
			}

			glClear(GL_COLOR_BUFFER_BIT);

			newTime = SDL_GetTicks();
			frameTime = newTime - curTime;

			// 如果因为暂停或者某一帧渲染时间过长导致
			// 真实时间间隔变长，重新设定帧时间
			if (frameTime >= frameLose) {
				frameTime = frameLose;
			}
			curTime = newTime;

			// 逻辑帧计数
			logicCount += frameTime;

			// 逻辑帧控制在 30 帧
			while (logicCount >= logicDelt) {
				Game::UpdateAll(&sdlEvent);
				logicCount -= logicDelt;
			}

			// 计算插值比率
			interpAlpha = static_cast<float>(logicCount) / 
				static_cast<float>(logicDelt);

			// 渲染游戏对象
			Game::DrawAll(shader, interpAlpha);

			// 双缓冲绘制
			SDL_GL_SwapWindow(window);

			// 当前帧时间限制, 稳定帧率，减少 CPU 损耗
			if (frameTime < rendDelt) {
				SDL_Delay(rendDelt - frameTime);
			}
		}

		shader.DeleteShader();
	}
}
