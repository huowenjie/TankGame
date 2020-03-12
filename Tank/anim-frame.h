#ifndef __ANIM_FRAME_H__
#define __ANIM_FRAME_H__

#include "game-obj.h"
#include "texture.h"

namespace hwj 
{
	// 逐帧动画
	class Animation : public GameObject
	{
	public:
		explicit Animation(
			float startX,
			float startY);
		~Animation();

		static const uint8_t ANIM_INITED;
		static const uint8_t ANIM_LOADED;
		static const uint8_t ANIM_LOOP;
		static const uint8_t ANIM_PLAYING;

	public:

		// 设置纹理信息
		void SetAnimTexInfo(const AnimTexInfo & texInfo);

		// 绘制对象
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// 更新当前位置
		void Update(GAMEEVNET handle);

		// 初始化
		void Initialize();
		void Terminate();

	public:
		// 设置播放模式
		void SetLoopMode(bool isLoop = true);
		bool IsLoop() const;

		// 设置/获取帧率
		void SetFps(int fps = 24);
		int GetFps() const;

		// 动画控制
		void Stop();
		void Play();
		bool IsPlaying();

	private:
		AnimTexInfo mTexInfo;		// 动画纹理信息
		int			mFrameIndex;	// 播放帧索引
		int			mFrameCount;	// 总帧数
		uint32_t	mFrameTime;		// 每帧时间
		uint32_t	mPlayingTime;	// 当前播放的时间
		uint32_t	mUpdateTime;	// 更新计时器
		uint8_t		mAnimStatus;	// 动画状态
	};
}

#endif // __ANIM_FRAME_H__
