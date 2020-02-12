#include "tank.h"
#include "app-debug.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace hwj 
{
	Tank::Tank() : x(400.0f), y(300.0f), width(60.0f), height(60.0f),
		speed(2.0f), direct(0.0f)
	{
		model = glm::mat4(1.0f);
		prevModel = glm::mat4(1.0f);

		startPos.x = x;
		startPos.y = y;
		startPos.z = 0.0f;
		startPos.w = 1.0f;
		position = startPos;
	}

	Tank::~Tank() 
	{
	}

	void Tank::Draw(ShaderProgram &shader, float interpAlgha)
	{
		shader.SetFloat("interpAlpha", interpAlgha);
		shader.SetMat4f("prevModel", &prevModel[0][0]);
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

		// 缓存上一帧的模型矩阵
		prevModel = model;

		// ------------- 基本操作逻辑 ---------------

		if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) { Move(Tank::UP);   }
		if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) { Move(Tank::DOWN); }
		if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) { Move(Tank::LEFT); }
		if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) { Move(Tank::RIGHT);}

		position = model * startPos;
	}

	void Tank::Move(MoveDirect md)
	{
		switch (md) {
		case UP:
			model = glm::translate(model, glm::vec3(0, speed, 0.0f));
			break;
		case DOWN:
			model = glm::translate(model, glm::vec3(0, -speed, 0.0f));
			break;
		case LEFT:
			model = glm::translate(model, glm::vec3(startPos.x, startPos.y, 0.0f));
			model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-startPos.x, -startPos.y, 0.0f));
			break;
		case RIGHT:
			model = glm::translate(model, glm::vec3(startPos.x, startPos.y, 0.0f));
			model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-startPos.x, -startPos.y, 0.0f));
			break;
		default:
			break;
		}

		LOG_INFO("x = %f, y = %f\n", position.x, position.y);
	}

	void Tank::Initialize()
	{
		float vertex[24] = {
			startPos.x - width / 2, startPos.y + height / 2, 0.0f, 0.0f,
			startPos.x + width / 2, startPos.y + height / 2, 0.0f, 0.0f,
			startPos.x + width / 2, startPos.y - height / 2, 0.0f, 0.0f,

			startPos.x + width / 2, startPos.y - height / 2, 0.0f, 0.0f,
			startPos.x - width / 2, startPos.y - height / 2, 0.0f, 0.0f,
			startPos.x - width / 2, startPos.y + height / 2, 0.0f, 0.0f
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
