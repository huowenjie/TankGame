#include "shell.h"
#include <glad/glad.h>
#include <sdl2/SDL.h>
#include <cmath>

#include "app-debug.h"
#include "texture.h"
#include "game.h"
#include "anim-frame.h"

namespace hwj 
{
	Shell::Shell(float x, float y) :
		GameObject("res/shell.png", x, y, 10.0f, 20.0f),
		mRange(300.0f),
		mSpeed(10.0f),
		mCurStatus(AWAIT)
	{
		mShellModel = glm::mat4(1.0f);
		mPrevShell = mShellModel;
	}

	Shell::~Shell()
	{
	}

	void Shell::Draw(ShaderProgram &shader, float interpAlgha) 
	{
		GameObject::Draw(shader, interpAlgha);

		shader.SetInt("turret", 1);
		shader.SetFloat("interpAlpha",	interpAlgha);
		shader.SetMat4f("prevModel",	&mPrevModel[0][0]);
		shader.SetMat4f("model",		&mModel[0][0]);
		shader.SetMat4f("turModel",		&mShellModel[0][0]);
		shader.SetMat4f("prevTur",		&mPrevShell[0][0]);

		glBindTexture(GL_TEXTURE_2D, mTex);
		glBindVertexArray(mVao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	// 更新当前位置
	void Shell::Update(WINDOWHANDLE handle) 
	{
		mPrevShell = mShellModel;

		switch (mCurStatus) {
		case FLYING:
			mShellModel = glm::translate(mShellModel, glm::vec3(0.0f, mSpeed, 0.0f));
			mPosition = mModel * mShellModel * mStartPos;

			// 判断射程
			if (IsOutOfRange()) {
				mCurStatus = EXPLODE;
			}
			break;

		case EXPLODE:
			Explode();
			break;

		case AWAIT:
		default:

			break;
		}

		GameObject::Update(handle);

		// -------------- 碰撞逻辑 ----------------

		std::map<ObjectCode, GameObject *> objs = Game::GetObjMap();
		std::map<ObjectCode, GameObject *>::const_iterator it =
			objs.begin();

		// 暂时先用此方法，以后再优化
		for (; it != objs.end(); ++it) {
			if (it->first == mTag.mCode) {
				continue;
			}

			GameObject *elem = it->second;

			if (Game::SphereCollision(*this, *elem)) {
				mCurStatus = EXPLODE;
				LOG_INFO("Explode!\n");
			}
		}
	}

	void Shell::SetSpeed(float speed)
	{
		mSpeed = speed;
	}

	bool Shell::IsOutOfRange() const
	{
		float sqx = mPosition.x - mShootPos.x;
		float sqy = mPosition.y - mShootPos.y;

		sqx = std::powf(sqx, 2.0f);
		sqy = std::powf(sqy, 2.0f);

		float dist = std::sqrtf(sqx + sqy);
		return dist >= mRange;
	}

	void Shell::Explode()
	{
		LOG_INFO("Explode! x = %f, y = %f\n", mPosition.x, mPosition.y);

		// 播放爆炸的动画并且
		Animation *anim = new Animation(mPosition.x, mPosition.y);
		anim->SetAnimTexInfo(GenAnimTextures("res/explode.png"));
		anim->SetTag(AllocObjTag(ANIM_TYPE));
		anim->Initialize();
		anim->SetLoopMode(false);
		anim->Play();

		Game::AddObj(anim->GetTag().mCode, anim);

		DestroySelf();
	}

	void Shell::Initialize() 
	{
		float vertex[24] = {
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y + mHeight / 2, 1.0f, 1.0f,
			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2, 1.0f, 0.0f,

			mStartPos.x + mWidth / 2, mStartPos.y - mHeight / 2, 1.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y - mHeight / 2, 0.0f, 0.0f,
			mStartPos.x - mWidth / 2, mStartPos.y + mHeight / 2, 0.0f, 1.0f
		};

		GameObject::Initialize(vertex, sizeof(vertex) / sizeof(float));
	}
	
	void Shell::Terminate() 
	{
		GameObject::Terminate();
	}
}
