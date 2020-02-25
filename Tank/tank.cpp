#include <glad/glad.h>
#include <sdl2/SDL.h>

#include "tank.h"
#include "app-debug.h"
#include "texture.h"

namespace hwj
{
	Tank::Tank(float x, float y) : 
		mWidth(60.0f), 
		mHeight(60.0f),
		mSpeed(2.0f),
		mRSpeed(1.0f),
		mVao(0),
		mVbo(0),
		mTex(0)
	{
		mModel = glm::mat4(1.0f);
		mPrevModel = glm::mat4(1.0f);

		mStartPos.x = x;
		mStartPos.y = y;
		mStartPos.z = 0.0f;
		mStartPos.w = 1.0f;
		mPosition = mStartPos;
	}

	Tank::~Tank() 
	{
	}

	void Tank::Draw(ShaderProgram &shader, float interpAlgha)
	{
		shader.SetInt("turret", 0);
		shader.SetFloat("interpAlpha", interpAlgha);
		shader.SetMat4f("prevModel", &mPrevModel[0][0]);
		shader.SetMat4f("model", &mModel[0][0]);

		glBindVertexArray(mVao);
		glBindTexture(GL_TEXTURE_2D, mTex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// ���þ���
		mTurret.Draw(shader, interpAlgha);
	}

	void Tank::Update(GAMEEVNET handle)
	{
		SDL_Event *gameEvent = reinterpret_cast<SDL_Event *>(handle);

		if (!handle) {
			return;
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		
		// ������һ֡��ģ�;���
		mPrevModel = mModel;
		mTurret.mPrevModel = mPrevModel;

		// ------------- ���������߼� ---------------

		if (state[SDL_SCANCODE_W]) { Run(Tank::UP);		}
		if (state[SDL_SCANCODE_S]) { Run(Tank::DOWN);	}
		if (state[SDL_SCANCODE_A]) { Run(Tank::LEFT);	}
		if (state[SDL_SCANCODE_D]) { Run(Tank::RIGHT);	}

		// ����̹�˵�ǰλ��
		mPosition = mModel * mStartPos;

		// ����������ģ�;���
		mTurret.Update(handle);
		mTurret.mModel = mModel;

		// -------------- ��ײ�߼� ----------------
	}

	void Tank::Run(Action action)
	{
		switch (action) {
		case UP:
			mModel = glm::translate(mModel, glm::vec3(0, mSpeed, 0.0f));
			break;
		case DOWN:
			mModel = glm::translate(mModel, glm::vec3(0, -mSpeed, 0.0f));
			break;
		case LEFT:
			mModel = glm::translate(mModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mModel = glm::rotate(mModel, glm::radians(mRSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mModel = glm::translate(mModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;
		case RIGHT:
			mModel = glm::translate(mModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mModel = glm::rotate(mModel, glm::radians(-mRSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mModel = glm::translate(mModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;
		case STOP:
		default:
			break;
		}
	}

	void Tank::SetSpeed(float speed)
	{
		mSpeed = speed;
	}

	// ����ת��
	void Tank::SetRotateSpeed(float rSpeed)
	{
		mRSpeed = rSpeed;
	}

	void Tank::Initialize()
	{
		float vertex[24] = {
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y + mHeight / 2, 1.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2, 1.0f, 0.0f,

			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2, 1.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y - mHeight / 2, 0.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 1.0f
		};

		// �������㻺�����
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)0);
		
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// ���������ļ�
		mTex = TexLoader::GenDefTextures("res/chassis.png");

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// ��ʼ������
		mTurret.mStartPos = mPosition;
		mTurret.Initialize();
	}

	void Tank::Terminate()
	{
		mTurret.Terminate();
		TexLoader::DelTextures(mTex);

		glDeleteBuffers(1, &mVbo);
		glDeleteVertexArrays(1, &mVao);		
	}
}
