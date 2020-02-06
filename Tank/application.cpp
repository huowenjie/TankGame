#include <glfw/glfw3.h>

#undef __gl_h_
#include <glad/glad.h>

#include "application.h"
#include "app-debug.h"
#include "shader.h"
#include "tank.h"

namespace hwj 
{
	Application::Application() : winWidth(800), winHeight(600)
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
			LOG_INTO("Failed to create GLFW window\n");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);
		mainWindow = window;
	}

	void Application::LoadGraphicApi() 
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			LOG_INTO("Failed to initialize GLAD\n");
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
		while (!glfwWindowShouldClose(win)) {
			glClear(GL_COLOR_BUFFER_BIT);

			// 游戏控制逻辑，比如操作对象移动
			tank.Update(mainWindow);

			// 游戏对象渲染
			tank.Draw(shader);

			glfwSwapBuffers(win);
			glfwPollEvents();
		}

		tank.Terminate();
		shader.DeleteShader();
	}
}
