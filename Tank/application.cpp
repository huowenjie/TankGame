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

		// ʹ�� opengl 4.5
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

		// ���� opengl �����Ķ���
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
		// ��ʼ�� glad
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

		// ����ͶӰ���󣬽� 800*600 �Ĵ���Ԫ��ͶӰ�� opengl -1��1 �ķ�Χ
		glm::mat4 projection = 
			glm::ortho(0.0f, (float)winWidth, 0.0f, (float)winHeight, -1.0f, 1.0f);
		shader.SetMat4f("projection", &projection[0][0]);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// ��ѭ��
		Uint32 logicDelt = 1000 / defLogicFps;
		Uint32 rendDelt  = 1000 / defRenderFps;
		Uint32 curTime   = SDL_GetTicks();

		Uint32 logicCount = 0;		// �߼����ʱ��
		Uint32 newTime    = 0;		// ÿ֡����ʱ��ʱ��
		Uint32 frameTime  = 0;		// ÿ����Ⱦ֡���õ�ʱ��
		Uint32 frameLose  = 250;	// ����֡ʱ�� ms
		float interpAlpha = 0.0f;	// ��ǰ֡�Ĳ�ֵ����

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

			// �����Ϊ��ͣ����ĳһ֡��Ⱦʱ���������
			// ��ʵʱ�����䳤�������趨֡ʱ��
			if (frameTime >= frameLose) {
				frameTime = frameLose;
			}
			curTime = newTime;

			// �߼�֡����
			logicCount += frameTime;

			// �߼�֡������ 30 ֡
			while (logicCount >= logicDelt) {
				Game::UpdateAll(&sdlEvent);
				logicCount -= logicDelt;
			}

			// �����ֵ����
			interpAlpha = static_cast<float>(logicCount) / 
				static_cast<float>(logicDelt);

			// ��Ⱦ��Ϸ����
			Game::DrawAll(shader, interpAlpha);

			// ˫�������
			SDL_GL_SwapWindow(window);

			// ��ǰ֡ʱ������, �ȶ�֡�ʣ����� CPU ���
			if (frameTime < rendDelt) {
				SDL_Delay(rendDelt - frameTime);
			}
		}

		shader.DeleteShader();
	}
}
