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
		Tank();
		~Tank();

		enum MoveDirect {
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
		void Move(MoveDirect md);

	public:
		// ��ʼ��
		void Initialize();
		void Terminate();

	protected:
		float x;				// ��ǰ������������λ��
		float y;
		float width;			// ��
		float height;			// ��

		float speed;			// ��ǰ�ƶ��ٶ�
		float direct;			// �������	

		unsigned int vao;
		unsigned int vbo;

		glm::mat4 model;		// ģ�;���
		glm::mat4 prevModel;	// ��һ֡��������
	};
}

#endif // __TANK_H__
