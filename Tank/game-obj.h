#ifndef __GAME_OBJ_H__
#define __GAME_OBJ_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "global.h"
#include "shader.h"

namespace hwj 
{
	// 游戏对象
	class GameObject 
	{
	public:
		GameObject(
			const std::string &resPath, float startX, float startY,
			float width,  float height);

		virtual ~GameObject();

	public:
		// 设置对象标识
		void SetTag(ObjectTag tag);

		// 获取对象标识
		ObjectTag GetTag() const;

		// 绘制对象
		virtual void Draw(ShaderProgram &shader, float interpAlgha = 1.0f) = 0;

		// 更新当前位置
		virtual void Update(GAMEEVNET handle) = 0;

	public:
		// 初始化
		virtual void Initialize(float *vertex, int num);
		virtual void Terminate();

	protected:
		ObjectTag mTag;

		float mWidth;			// 宽
		float mHeight;			// 高

		unsigned int mVao;
		unsigned int mVbo;
		unsigned int mTex;

		glm::mat4 mModel;		// 模型矩阵
		glm::mat4 mPrevModel;	// 上一帧矩阵数据
		glm::vec4 mPosition;	// 位置
		glm::vec4 mStartPos;	// 初始位置

		std::string mResPath;	// 资源路径
	};
}

#endif // __GAME_OBJ_H__
