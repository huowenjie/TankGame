#include <glad/glad.h>
#include <sdl2/SDL.h>
#include <cstring>

#include "app-debug.h"
#include "anim-frame.h"

namespace hwj 
{
	const uint8_t Animation::ANIM_INITED  = 0x01;
	const uint8_t Animation::ANIM_LOADED  = 0x02;
	const uint8_t Animation::ANIM_LOOP	  = 0x04;
	const uint8_t Animation::ANIM_PLAYING = 0x08;

	Animation::Animation(
		float startX, float startY) :
		GameObject("", startX, startY, 60.0f, 60.0f),
		mFrameIndex(0),
		mFrameCount(0),
		mFrameTime(1000 / 24),
		mPlayingTime(0),
		mUpdateTime(0),
		mAnimStatus(0)
	{
	}

	Animation::~Animation() 
	{
	}

	void Animation::SetAnimTexInfo(const AnimTexInfo &texInfo)
	{
		mTexInfo = texInfo;
		mFrameCount = (mTexInfo.mNum <= 0) ? 1 : mTexInfo.mNum;
		mFrameIndex = 0;
		mAnimStatus |= ANIM_LOADED;
	}

	void Animation::Draw(ShaderProgram &shader, float interpAlgha) 
	{
		// 不允许播放则禁止渲染
		if ((mAnimStatus & ANIM_PLAYING) != ANIM_PLAYING) {
			return;
		}

		GameObject::Draw(shader, interpAlgha);

		shader.SetFloat("interpAlpha", interpAlgha);
		shader.SetMat4f("prevModel", &mPrevModel[0][0]);
		shader.SetMat4f("model", &mModel[0][0]);

		glBindTexture(GL_TEXTURE_2D, mVertObj.mTex);
		glBindVertexArray(mVertObj.mVao);
		glDrawArrays(GL_TRIANGLES, mFrameIndex * 6, 6);
		glBindVertexArray(0);
	}

	void Animation::Update(GAMEEVNET handle)
	{
		if ((mAnimStatus & ANIM_PLAYING) == ANIM_PLAYING) {
			if (mFrameIndex >= mFrameCount) {
				if ((mAnimStatus & ANIM_LOOP) != ANIM_LOOP) {
					mAnimStatus &= (~ANIM_PLAYING);
				}

				// 如果不循环播放，直接销毁对象
				if (((mAnimStatus & ANIM_LOOP) == ANIM_LOOP)) {
					mFrameIndex = 0;
				} else {
					DestroySelf();
				}
			}
			else {
				// 控制动画播放帧率
				if (mUpdateTime == 0) {
					mUpdateTime = SDL_GetTicks();
				}

				uint32_t curTime = SDL_GetTicks();

				mPlayingTime += (curTime - mUpdateTime);

				if (mPlayingTime >= mFrameTime) {
					// 播放下一帧
					mFrameIndex++;
					mPlayingTime = mPlayingTime % mFrameTime;
					mUpdateTime = curTime;
				}
			}
		}
	}

	void Animation::Initialize()
	{
		if (mFrameCount <= 0) {
			LOG_INFO("Frame only is 1!\n");
			mFrameCount = 1;
		}

		float *textureVertex = new float[24 * mFrameCount];
		float tmpIndex = 0.0f;

		for (int i = 0, j = 24 * mFrameCount; i < j; i += 24) {
			textureVertex[i] = -0.5f;
			textureVertex[i + 1] = 0.5f;

			textureVertex[i + 2] = tmpIndex / mFrameCount;
			textureVertex[i + 3] = 1.0f;

			textureVertex[i + 4] = 0.5f;
			textureVertex[i + 5] = 0.5f;

			textureVertex[i + 6] = (tmpIndex + 1.0f) / mFrameCount;
			textureVertex[i + 7] = 1.0f;

			textureVertex[i + 8] = 0.5f;
			textureVertex[i + 9] = -0.5f;

			textureVertex[i + 10] = (tmpIndex + 1.0f) / mFrameCount;
			textureVertex[i + 11] = 0.0f;

			textureVertex[i + 12] = 0.5f;
			textureVertex[i + 13] = -0.5f;

			textureVertex[i + 14] = (tmpIndex + 1.0f) / mFrameCount;
			textureVertex[i + 15] = 0.0f;

			textureVertex[i + 16] = -0.5f;
			textureVertex[i + 17] = -0.5f;

			textureVertex[i + 18] = tmpIndex / mFrameCount;
			textureVertex[i + 19] = 0.0f;

			textureVertex[i + 20] = -0.5f;
			textureVertex[i + 21] = 0.5f;

			textureVertex[i + 22] = tmpIndex / mFrameCount;
			textureVertex[i + 23] = 1.0f;

			tmpIndex += 1.0f;
		}

		mVertObj.mTex = mTexInfo.mTex;

		// 创建顶点缓冲对象
		GameObject::LoadVertex(textureVertex, 24 * mFrameCount);
		GameObject::Initialize();

		if (!GameObject::IsVertexObjExist(ANIM_TYPE)) {
			GameObject::AddVertexObj(ANIM_TYPE, mVertObj);
		}

		delete[] textureVertex;
		mAnimStatus |= ANIM_INITED;
	}

	void Animation::Terminate() 
	{
		GameObject::Terminate();
		mAnimStatus = 0;
	}

	void Animation::SetLoopMode(bool isLoop)
	{
		mAnimStatus = isLoop ? (mAnimStatus | ANIM_LOOP) : 
			(mAnimStatus & (~ANIM_LOOP));
	}

	bool Animation::IsLoop() const 
	{
		return ((mAnimStatus & ANIM_LOOP) == ANIM_LOOP);
	}

	// 设置/获取帧率
	void Animation::SetFps(int fps)
	{
		mFrameTime = (fps <= 0 || fps >= 60) ? (1000 / 24) : (1000 / fps);
	}
	
	int Animation::GetFps() const 
	{
		return (mFrameTime == 0) ? 24 : (1000 / mFrameTime);
	}

	void Animation::Stop() 
	{
		mAnimStatus &= (~ANIM_PLAYING);
		mFrameIndex = 0;
	}
	
	void Animation::Play()
	{
		if (((mAnimStatus & ANIM_INITED) == ANIM_INITED) &&
			((mAnimStatus & ANIM_LOADED) == ANIM_LOADED)) {
			mAnimStatus |= ANIM_PLAYING;
		}
	}
	
	bool Animation::IsPlaying() 
	{
		return (mAnimStatus & ANIM_PLAYING) == ANIM_PLAYING;
	}
}
