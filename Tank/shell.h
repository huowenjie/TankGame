#ifndef __SHELL_H__
#define __SHELL_H__

#include <vector>
#include "turret.h"

namespace hwj 
{
	// �ڵ�
	class Shell : public GameObject
	{
	public:
		friend class Turret;

		Shell(float x = 0.0f, float y = 0.0f);
		~Shell();

		enum Status {
			AWAIT,		// ����
			FLYING,		// ������й���
			EXPLODE,	// ��ը
			STRIKE,		// ײ��
			DESTROY		// ��ϵͳ����
		};

	public:
		// ���ƶ���
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// ���µ�ǰλ��
		void Update(WINDOWHANDLE handle);

		// ��������
		void SetSpeed(float speed);

		// �ڵ��Ƿ񳬳���Χ
		bool IsOutOfRange() const;

	public:
		// ��ʼ��
		void Initialize();
		void Terminate();

	protected:
		glm::mat4 mShellModel;	// �ڵ�λ��ģ�;���
		glm::mat4 mPrevShell;	// ��һ֡�ڵ�ģ�;���
		glm::vec4 mShootPos;	// ����λ��

		float  mRange;			// ���
		float  mSpeed;			// ��ǰ�ƶ��ٶ�
		Status mCurStatus;		// ��ǰ״̬
	};
}

#endif // __SHELL_H__
