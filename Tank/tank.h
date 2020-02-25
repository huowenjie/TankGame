#ifndef __TANK_H__
#define __TANK_H__

#include "turret.h"

namespace hwj 
{
	class Tank 
	{
	public:
		Tank(float x = 400.0f, float y = 300.0f);
		~Tank();

		enum Action {
			UP,
			DOWN,
			LEFT,
			RIGHT,
			STOP
		};

	public:

		// ���ƶ���
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// ���µ�ǰλ��
		void Update(GAMEEVNET handle);

		// �ƶ�
		void Run(Action action);

		// ��������
		void SetSpeed(float speed);

		// ����ת��
		void SetRotateSpeed(float rSpeed);

	public:
		// ��ʼ��
		void Initialize();
		void Terminate();

	protected:
		float mWidth;			// ��
		float mHeight;			// ��

		float mSpeed;			// ��ǰ�ƶ��ٶ�
		float mRSpeed;			// ������ת�ٶ�

		unsigned int mVao;
		unsigned int mVbo;
		unsigned int mTex;

		glm::mat4 mModel;		// ģ�;���
		glm::mat4 mPrevModel;	// ��һ֡��������
		glm::vec4 mPosition;	// λ��
		glm::vec4 mStartPos;	// ��ʼλ��

		Turret mTurret;			// ��������
	};
}

#endif // __TANK_H__
