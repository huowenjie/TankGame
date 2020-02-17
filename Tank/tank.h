#ifndef __TANK_H__
#define __TANK_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "global.h"
#include "shader.h"

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
		void Update(WINDOWHANDLE handle);

		// �ƶ�
		void Move(Action action);

		// ��������
		void SetSpeed(int speed);

	public:
		// ��ʼ��
		void Initialize();
		void Terminate();

	protected:
		float mWidth;			// ��
		float mHeight;			// ��

		float mSpeed;			// ��ǰ�ƶ��ٶ�

		unsigned int mVao;
		unsigned int mVbo;

		glm::mat4 mModel;		// ģ�;���
		glm::mat4 mPrevModel;	// ��һ֡��������
		glm::vec4 mPosition;	// λ��
		glm::vec4 mStartPos;	// ��ʼλ��
	};
}

#endif // __TANK_H__
