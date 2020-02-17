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

		// ��ѭ��
		float logicDelt = 1.0f / defLogicFps;
		float rendDelt = 1.0f / defRenderFps;

		float logicCount = 0.0f;				// �߼����ʱ��
		float curTime = (float)glfwGetTime();
		float newTime = 0.0f;					// ÿ֡����ʱ��ʱ��
		float frameTime = 0.0f;					// ÿ����Ⱦ֡���õ�ʱ��
		float frameLose = 0.25f;				// ����֡ʱ��
		float interpAlpha = 0.0f;				// ��ǰ֡�Ĳ�ֵ����

		TIMER tm = NULL;

		if (!CreateTimer(tm) || !tm) {
			LOG_INFO("CreateTimer error!\n");
			return;
		}

		while (!glfwWindowShouldClose(win)) {
			glClear(GL_COLOR_BUFFER_BIT);

			newTime = (float)glfwGetTime();
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

				// ��Ϸ�����߼���������������ƶ�
				tank.Update(mainWindow);
				logicCount -= logicDelt;
			}

			// �����ֵ����
			interpAlpha = logicCount / logicDelt;

			// ��Ϸ������Ⱦ
			tank.Draw(shader, interpAlpha);

			// ˫�������
			glfwSwapBuffers(win);
			glfwPollEvents();

			// ��ǰ֡ʱ������, w �ȶ�֡��
			if (frameTime < rendDelt) {
				WaitTimer(tm, (int)(1000 * (rendDelt - frameTime)));
			}
		}

		DestroyTimer(tm);

		tank.Terminate();
		shader.DeleteShader();
	}
}
