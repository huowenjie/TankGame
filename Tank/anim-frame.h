#ifndef __ANIM_FRAME_H__
#define __ANIM_FRAME_H__

#include "game-obj.h"
#include "texture.h"

namespace hwj 
{
	// ��֡����
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

		// ����������Ϣ
		void SetAnimTexInfo(const AnimTexInfo & texInfo);

		// ���ƶ���
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// ���µ�ǰλ��
		void Update(GAMEEVNET handle);

		// ��ʼ��
		void Initialize();
		void Terminate();

	public:
		// ���ò���ģʽ
		void SetLoopMode(bool isLoop = true);
		bool IsLoop() const;

		// ����/��ȡ֡��
		void SetFps(int fps = 24);
		int GetFps() const;

		// ��������
		void Stop();
		void Play();
		bool IsPlaying();

	private:
		AnimTexInfo mTexInfo;		// ����������Ϣ
		int			mFrameIndex;	// ����֡����
		int			mFrameCount;	// ��֡��
		uint32_t	mFrameTime;		// ÿ֡ʱ��
		uint32_t	mPlayingTime;	// ��ǰ���ŵ�ʱ��
		uint32_t	mUpdateTime;	// ���¼�ʱ��
		uint8_t		mAnimStatus;	// ����״̬
	};
}

#endif // __ANIM_FRAME_H__
