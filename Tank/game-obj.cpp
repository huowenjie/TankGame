#include <glad/glad.h>

#include "game-obj.h"
#include "texture.h"

namespace hwj 
{
	GameObject::GameObject(
		const std::string &resPath, float startX, float startY,
		float width, float height) :
		mTag(0),
		mWidth(width),
		mHeight(height),
		mVao(0),
		mVbo(0),
		mTex(0),
		mResPath(resPath)
	{
		mModel = glm::mat4(1.0f);
		mPrevModel = mModel;

		mStartPos.x = startX;
		mStartPos.y = startY;
		mStartPos.z = 0.0f;
		mStartPos.w = 1.0f;
		mPosition = mStartPos;		
	}

	GameObject::~GameObject() 
	{
	}

	void GameObject::SetTag(ObjectTag tag)
	{
		mTag = tag;
	}

	ObjectTag GameObject::GetTag() const
	{
		return mTag;
	}

	void GameObject::Initialize(float *vertex, int num)
	{
		if (!vertex || num <= 0) {
			return;
		}

		// 创建顶点缓冲对象
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, num * sizeof(float), vertex, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 加载纹理文件
		mTex = TexLoader::GenDefTextures(mResPath.c_str());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void GameObject::Terminate() 
	{
		TexLoader::DelTextures(mTex);

		glDeleteBuffers(1, &mVbo);
		glDeleteVertexArrays(1, &mVao);
	}
}
