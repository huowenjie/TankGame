#include <glad/glad.h>
#include <cmath>

#include "game-obj.h"
#include "texture.h"
#include "game.h"

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
		
		// 设置外接圆半径
		mSphere.mZ = 
			((mWidth > mHeight) ? mHeight : mWidth) / 2.0f;
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

	void GameObject::Draw(ShaderProgram &shader, float interpAlgha)
	{
	}

	// 更新当前位置
	void GameObject::Update(GAMEEVNET handle)
	{
		// 更新包围盒子
		mAABB.mA = mPosition.x - mWidth / 2;
		mAABB.mB = mPosition.x + mWidth / 2;
		mAABB.mC = mPosition.y - mWidth / 2;
		mAABB.mD = mPosition.y + mWidth / 2;

		// 更新包围球
		mSphere.mX = mPosition.x;
		mSphere.mY = mPosition.y;
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

	Vector2D<float> GameObject::GetPosition() const
	{
		return Vector2D<float>(mPosition.x, mPosition.y);
	}

	const Vector4D<float> & GameObject::GetAABB() const
	{
		return mAABB;
	}

	const Vector3D<float> & GameObject::GetBoundingSphere() const
	{
		return mSphere;
	}

	void GameObject::DestroySelf()
	{
		GameObject *obj = Game::RemoveObj(mTag);

		if (obj) {
			obj->Terminate();
			delete obj;
		}
	}
}
