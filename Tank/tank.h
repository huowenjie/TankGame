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
		// 绘制对象
		void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// 更新当前位置
		void Update(WINDOWHANDLE handle);

		// 移动
		void Move(Action action);

		// 设置移速
		void SetSpeed(int speed);

	public:
		// 初始化
		void Initialize();
		void Terminate();

	protected:
		float mWidth;			// 宽
		float mHeight;			// 高

		float mSpeed;			// 当前移动速度

		unsigned int mVao;
		unsigned int mVbo;

		glm::mat4 mModel;		// 模型矩阵
		glm::mat4 mPrevModel;	// 上一帧矩阵数据
		glm::vec4 mPosition;	// 位置
		glm::vec4 mStartPos;	// 初始位置
	};
}

#endif // __TANK_H__
