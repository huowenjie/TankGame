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

		glBindTexture(GL_TEXTURE_2D, mTex);
		glBindVertexArray(mVao);
		glDrawArrays(GL_TRIANGLES, mFrameIndex * 12, 6);
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
			textureVertex[i] = mStartPos.x - mWidth / 2,
			textureVertex[i + 1] = mStartPos.y + mHeight / 2,
			textureVertex[i + 2] = mStartPos.x + mWidth  / 2,
			textureVertex[i + 3] = mStartPos.y + mHeight / 2,
			textureVertex[i + 4] = mStartPos.x + mWidth  / 2,
			textureVertex[i + 5] = mStartPos.y - mHeight / 2,

			textureVertex[i + 6] = mStartPos.x + mWidth  / 2,
			textureVertex[i + 7] = mStartPos.y - mHeight / 2,
			textureVertex[i + 8] = mStartPos.x - mWidth  / 2,
			textureVertex[i + 9] = mStartPos.y - mHeight / 2,
			textureVertex[i + 10] = mStartPos.x - mWidth / 2,
			textureVertex[i + 11] = mStartPos.y + mHeight / 2,

			textureVertex[i + 12] = tmpIndex / mFrameCount;
			textureVertex[i + 13] = 1.0f;
			textureVertex[i + 14] = (tmpIndex + 1.0f) / mFrameCount;
			textureVertex[i + 15] = 1.0f;
			textureVertex[i + 16] = (tmpIndex + 1.0f) / mFrameCount;
			textureVertex[i + 17] = 0.0f;

			textureVertex[i + 18] = (tmpIndex + 1.0f) / mFrameCount;
			textureVertex[i + 19] = 0.0f;
			textureVertex[i + 20] = tmpIndex / mFrameCount;
			textureVertex[i + 21] = 0.0f;
			textureVertex[i + 22] = tmpIndex / mFrameCount;
			textureVertex[i + 23] = 1.0f;

			tmpIndex += 1.0f;
		}

		// 创建顶点缓冲对象
		glCreateVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glCreateBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glNamedBufferStorage(mVbo, 24 * mFrameCount * sizeof(float), textureVertex, GL_DYNAMIC_STORAGE_BIT);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)(12 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 加载纹理文件
		if (!glIsTexture(mTex) && !mResPath.empty()) {
			mTex = GenDefTextures(mResPath.c_str());
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		mTex = mTexInfo.mTex;

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
