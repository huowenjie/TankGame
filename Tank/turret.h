#ifndef __TURRET_H__
#define __TURRET_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "global.h"
#include "shader.h"

namespace hwj 
{
	class Tank;
	// ����
	class Turret 
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
		void Update(WINDOWHANDLE handle);

		// ����
		void Run(Action action);

	public:
		// ��ʼ����ֹ
		void Initialize();
		void Terminate();

	protected:
		float mWidth;			// ��
		float mHeight;			// ��

		unsigned int mVao;
		unsigned int mVbo;
		unsigned int mTex;

		float mRotateSpeed;		// ��ǰ����ת��
		float mRotateAngle;		// ������ת�Ƕ�

		glm::mat4 mModel;		// ����ģ�;���
		glm::mat4 mPrevModel;	// ��һ֡��������
		glm::mat4 mTurModel;	// ����ģ�;���
		glm::mat4 mPrevTur;		// ��һ֡����ģ�;���
		glm::vec4 mStartPos;	// ��ʼλ��

		Tank *mChassic;			// ����̹�˵���
	};
}

#endif // __TURRET_H__
