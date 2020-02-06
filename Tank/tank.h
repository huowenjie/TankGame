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
		// 绘制对象
		void Draw(ShaderProgram &shader);

		// 更新当前位置
		void Update(WINDOWHANDLE handle);

		// 移动
		void Move(MoveDirect md);

	public:
		// 初始化
		void Initialize();
		void Terminate();

	protected:
		float x;			// 当前物体中心坐标位置
		float y;
		float width;		// 宽
		float height;		// 高

		float speed;		// 当前移动速度
		float direct;		// 对象方向角	

		unsigned int vao;
		unsigned int vbo;

		glm::mat4 model;	// 平移矩阵
	};
}

#endif // __TANK_H__
