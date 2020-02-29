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
		virtual void Draw(ShaderProgram &shader, float interpAlgha = 1.0f) = 0;

		// ���µ�ǰλ��
		virtual void Update(GAMEEVNET handle) = 0;

	public:
		// ��ʼ��
		virtual void Initialize(float *vertex, int num);
		virtual void Terminate();

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

		std::string mResPath;	// ��Դ·��
	};
}

#endif // __GAME_OBJ_H__
