#include "tank.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>

namespace hwj 
{
	Tank::Tank() : x(400.0f), y(300.0f), width(60.0f), height(60.0f),
		speed(2.0f), direct(0.0f)
	{
		model = glm::mat4(1.0f);
	}

	Tank::~Tank() 
	{
	}

	void Tank::Draw(ShaderProgram &shader)
	{
		shader.SetMat4f("model", &model[0][0]);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void Tank::Update(WINDOWHANDLE handle)
	{
		if (!handle) {
			return;
		}

		GLFWwindow *win = (GLFWwindow *)handle;

		if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
			Move(Tank::UP);
		}

		if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
			Move(Tank::DOWN);
		}

		if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
			Move(Tank::LEFT);
		}

		if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
			Move(Tank::RIGHT);
		}
	}

	void Tank::Move(MoveDirect md)
	{
		static glm::vec3 up    = glm::vec3(0.0f,   speed, 0.0f);
		static glm::vec3 down  = glm::vec3(0.0f,  -speed, 0.0f);
		static glm::vec3 left  = glm::vec3(-speed, 0.0f,  0.0f);
		static glm::vec3 right = glm::vec3(speed,  0.0f,  0.0f);

		switch (md) {
		case UP:	model = glm::translate(model, up); break;
		case DOWN:	model = glm::translate(model, down); break;
		case LEFT:	model = glm::translate(model, left); break;
		case RIGHT: model = glm::translate(model, right); break;
		default:	model = glm::mat4(1.0f);
			break;
		}
	}

	void Tank::Initialize()
	{
		float vertex[24] = {
			x - width / 2, y + height / 2, 0.0f, 0.0f,
			x + width / 2, y + height / 2, 0.0f, 0.0f,
			x + width / 2, y - height / 2, 0.0f, 0.0f,
			x + width / 2, y - height / 2, 0.0f, 0.0f,
			x - width / 2, y - height / 2, 0.0f, 0.0f,
			x - width / 2, y + height / 2, 0.0f, 0.0f,
		};

		// 创建顶点缓冲对象
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Tank::Terminate()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}
}
