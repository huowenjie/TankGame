#include <glfw/glfw3.h>

#undef __gl_h_
#include <glad/glad.h>

#include "application.h"
#include "app-debug.h"
#include "shader.h"
#include "tank.h"

namespace hwj 
{
	Application::Application() : 
		winWidth(800), 
		winHeight(600),
		defRenderFps(60.0f),
		defLogicFps(30.0f)
	{
	}
	
	Application::Application(int width, int height) :
		winWidth(width), winHeight(height)
	{
	}

	Application::~Application() 
	{
		if (mainWindow != NULL) {
			glfwTerminate();
		}
	}

	void Application::CreateWindow(const char *title)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, title, NULL, NULL);
		
		if (!window) {
			LOG_INFO("Failed to create GLFW window\n");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);
		mainWindow = window;
	}

	void Application::LoadGraphicApi() 
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			LOG_INFO("Failed to initialize GLAD\n");
		}
	}

	void Application::Render() 
	{
		if (!mainWindow) {
			return;
		}

		GLFWwindow *win = (GLFWwindow *)mainWindow;

		ShaderProgram shader;

		shader.LoadShaderFile("triangle.vert", "triangle.frag");
		shader.UseProgram();

		glm::mat4 projection = 
			glm::ortho(0.0f, (float)winWidth, 0.0f, (float)winHeight, -1.0f, 1.0f);
		shader.SetMat4f("projection", &projection[0][0]);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		Tank tank;
		tank.Initialize();

		// 主循环
		float logicDelt = 1.0f / defLogicFps;
		float rendDelt = 1.0f / defRenderFps;

		float logicCount = 0.0f;				// 逻辑贞计时器
		float curTime = (float)glfwGetTime();
		float newTime = 0.0f;					// 每帧开启时的时间
		float frameTime = 0.0f;					// 每个渲染帧所用的时间
		float frameLose = 0.25f;				// 最大掉帧时间
		float interpAlpha = 0.0f;				// 当前帧的插值比率

		TIMER tm = NULL;

		if (!CreateTimer(tm) || !tm) {
			LOG_INFO("CreateTimer error!\n");
			return;
		}

		while (!glfwWindowShouldClose(win)) {
			glClear(GL_COLOR_BUFFER_BIT);

			newTime = (float)glfwGetTime();
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

				// 游戏控制逻辑，比如操作对象移动
				tank.Update(mainWindow);
				logicCount -= logicDelt;
			}

			// 计算插值比率
			interpAlpha = logicCount / logicDelt;

			// 游戏对象渲染
			tank.Draw(shader, interpAlpha);

			// 双缓冲绘制
			glfwSwapBuffers(win);
			glfwPollEvents();

			// 当前帧时间限制, w 稳定帧率
			if (frameTime < rendDelt) {
				WaitTimer(tm, (int)(1000 * (rendDelt - frameTime)));
			}
		}

		DestroyTimer(tm);

		tank.Terminate();
		shader.DeleteShader();
	}
}
