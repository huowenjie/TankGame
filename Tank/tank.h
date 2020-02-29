#ifndef __TANK_H__
#define __TANK_H__

#include "turret.h"

namespace hwj 
{
	class Tank : public GameObject
	{
	public:
		Tank(RoleType type, float x = 400.0f, float y = 300.0f);
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
		RoleType mType;			// ��ɫ����

		float mSpeed;			// ��ǰ�ƶ��ٶ�
		float mRSpeed;			// ������ת�ٶ�

		Turret mTurret;			// ��������
	};
}

#endif // __TANK_H__
