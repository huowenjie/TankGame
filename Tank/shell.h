#ifndef __SHELL_H__
#define __SHELL_H__

#include "turret.h"

namespace hwj 
{
	// �ڵ�
	class Shell
	{
	public:
		Shell();
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
		void SetSpeed(int speed);

	public:
		// ��ʼ��
		void Initialize();
		void Terminate();

	protected:
		float mWidth;			// ��
		float mHeight;			// ��

		unsigned int mVao;
		unsigned int mVbo;
		unsigned int mTex;

		float mSpeed;			// ��ǰ�ƶ��ٶ�

		glm::mat4 mModel;		// ģ�;���
		glm::mat4 mPrevModel;	// ��һ֡��������
		glm::vec4 mPosition;	// λ��
		glm::vec4 mStartPos;	// ��ʼλ��
	};
}

#endif // __SHELL_H__
