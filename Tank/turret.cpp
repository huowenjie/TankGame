#include <cmath>
#include <glad/glad.h>
#include <sdl2/SDL.h>

#include "game.h"
#include "shell.h"

#include "app-debug.h"
#include "texture.h"

namespace hwj 
{
	Turret::Turret(Tank *chassic) : 
		GameObject("res/turret.png", 0, 0, 30.0f, 70.0f),
		mShootInterval(500U),
		mRotateSpeed(1.0f),
		mRotateAngle(0.0f),
		mChassic(chassic)
	{
		mTurModel = mModel;
		mPrevTur = mModel;
	}

	Turret::~Turret()
	{
	}

	void Turret::SetController(Tank *chassic)
	{
		mChassic = chassic;
	}

	// 绘制对象
	void Turret::Draw(ShaderProgram &shader, float interpAlgha)
	{
		shader.SetInt("turret", 1);
		shader.SetFloat("interpAlpha",	interpAlgha);
		shader.SetMat4f("prevModel",	&mPrevModel[0][0]);
		shader.SetMat4f("model",		&mModel[0][0]);
		shader.SetMat4f("turModel",		&mTurModel[0][0]);
		shader.SetMat4f("prevTur",		&mPrevTur[0][0]);

		glBindTexture(GL_TEXTURE_2D, mTex);
		glBindVertexArray(mVao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	// 更新当前位置
	void Turret::Update(GAMEEVNET handle)
	{
		SDL_Event *gameEvent = reinterpret_cast<SDL_Event *>(handle);

		if (!handle) {
			return;
		}

		const Uint8 *state = SDL_GetKeyboardState(NULL);
		mPrevTur = mTurModel;
		
		// ------------- 基本操作逻辑 ---------------

		if (state[SDL_SCANCODE_Q])		{ Run(LEFTROTATE);  }
		if (state[SDL_SCANCODE_E])		{ Run(RIGHTROTATE); }
		if (state[SDL_SCANCODE_SPACE])	{ Fire();			}
	}

	// 旋转
	void Turret::Run(Action action) 
	{
		switch (action)
		{
		case LEFTROTATE:
			mTurModel = glm::translate(mTurModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mTurModel = glm::rotate(mTurModel, glm::radians(mRotateSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mTurModel = glm::translate(mTurModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;

		case RIGHTROTATE:
			mTurModel = glm::translate(mTurModel, glm::vec3(mStartPos.x, mStartPos.y, 0.0f));
			mTurModel = glm::rotate(mTurModel, glm::radians(-mRotateSpeed), glm::vec3(0.0f, 0.0f, 1.0f));
			mTurModel = glm::translate(mTurModel, glm::vec3(-mStartPos.x, -mStartPos.y, 0.0f));
			break;

		default:
			break;
		}
	}

	void Turret::Fire()
	{
		static bool isReady = true;
		static Uint32 prevTime = 0;
		Uint32 curTime = SDL_GetTicks();

		if (isReady) {
			isReady = false;
			LOG_INFO("Fire!\n");

			Shell *shell = new Shell(mStartPos.x, mStartPos.y);

			ObjectTag tag = AllocConsumable();
			
			shell->SetTag(tag);
			shell->mModel = mModel;
			shell->mShellModel = glm::translate(mTurModel,
				glm::vec3(0.0f, 50.0f, 0.0f));

			shell->mShootPos = 
				mModel * shell->mShellModel * mStartPos;

			shell->mPrevModel = mPrevModel;
			shell->mPrevShell = shell->mShellModel;
			shell->mCurStatus = Shell::FLYING;
			shell->Initialize();

			Game::AddObj(tag, shell);
			prevTime = SDL_GetTicks() + mShootInterval;
		} else {
			LOG_INFO("Filling!\n");
		}

		if (!SDL_TICKS_PASSED(prevTime, curTime)) {
			isReady = true;
		}
	}

	// 初始化终止
	void Turret::Initialize() 
	{
		float vertex[24] = {
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2 + 12.0f, 0.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y + mHeight / 2 + 12.0f, 1.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2 + 12.0f, 1.0f, 0.0f,

			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2 + 12.0f, 1.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y - mHeight / 2 + 12.0f, 0.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2 + 12.0f, 0.0f, 1.0f
		};

		GameObject::Initialize(vertex, sizeof(vertex) / sizeof(float));
	}

	void Turret::Terminate()
	{
		GameObject::Terminate();
	}
}
