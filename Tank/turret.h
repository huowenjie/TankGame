#ifndef __TURRET_H__
#define __TURRET_H__

#include "game-obj.h"

namespace hwj 
{
	class Tank;

	// ����
	class Turret : public GameObject
	{
	public:
		friend class Tank;

		explicit Turret(Tank *chassic = nullptr);
		~Turret();

		enum Action {
			FILLING,		// װ����
			STOP,			// ֹͣ��ת
			LEFTROTATE,		// ����ת
			RIGHTROTATE		// ����ת
		};

	public:

		void SetController(Tank *chassic);

		// ���ƶ���
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// ���µ�ǰλ��
		void Update(GAMEEVNET handle);

		// ����
		void Run(Action action);

		// ����
		void Fire();

	public:

		// ��ʼ��
		void Initialize();

		// ��ֹ
		void Terminate();

	protected:
		unsigned int mShootInterval;	// ������ ms

		float mRotateSpeed;				// ��ǰ����ת��
		float mRotateAngle;				// ������ת�Ƕ�

		glm::mat4 mTurModel;			// ����ģ�;���
		glm::mat4 mPrevTur;				// ��һ֡����ģ�;���

		Tank *mChassic;					// ����̹�˵���
	};
}

#endif // __TURRET_H__
