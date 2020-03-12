#ifndef __GAME_OBJ_H__
#define __GAME_OBJ_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "global.h"
#include "shader.h"
#include "game-math.h"

namespace hwj
{
	// ��Ϸ����
	class GameObject 
	{
	public:
		GameObject(
			const std::string &resPath, float startX, float startY,
			float width,  float height);

		virtual ~GameObject();

	public:
		// ���ö����ʶ
		void SetTag(ObjectTag tag);

		// ��ȡ�����ʶ
		ObjectTag GetTag() const;

		// ���ƶ���
		virtual void Draw(ShaderProgram &shader, float interpAlgha = 1.0f);

		// ���µ�ǰλ��
		virtual void Update(GAMEEVNET handle);

	public:
		// ��ʼ��
		virtual void Initialize(float *vertex, int num);
		virtual void Terminate();

		// ��ȡ��ǰ��������
		Vector2D<float> GetPosition() const;

		// ��ȡ��Χ������
		const Vector4D<float> & GetAABB() const;

		// ��ȡ��Χ������
		const Vector3D<float> & GetBoundingSphere() const;

	protected:

		// ��������
		void DestroySelf();

	protected:
		ObjectTag mTag;

		float mWidth;			// ��
		float mHeight;			// ��

		unsigned int mVao;
		unsigned int mVbo;
		unsigned int mTex;

		glm::mat4 mModel;		// ģ�;���
		glm::mat4 mPrevModel;	// ��һ֡��������
		glm::vec4 mPosition;	// λ��
		glm::vec4 mStartPos;	// ��ʼλ��

		Vector4D<float> mAABB;	// ��Χ��
		Vector3D<float> mSphere;// ��Χ��

		std::string mResPath;	// ��Դ·��
	};
}

#endif // __GAME_OBJ_H__
