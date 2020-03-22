#include <glad/glad.h>
#include <sdl2/SDL.h>

#include "app-debug.h"
#include "game-map.h"
#include "texture.h"

namespace hwj 
{
	GameMap::GameMap(
		float x, float y, float width, float height) :
		GameObject(x, y, width, height),
		mDeltX(5.0f),
		mDeltY(5.0f)
	{
		mCamera = glm::mat4(1.0f);
		mProjection = mCamera;
		mPrevProj = mProjection;
	}

	GameMap::~GameMap()
	{
	}

	void GameMap::Draw(ShaderProgram &shader, float interpAlgha)
	{
		GameObject::Draw(shader, interpAlgha);

		shader.SetFloat("interpAlpha", interpAlgha);
		shader.SetMat4f("prevModel", &mPrevModel[0][0]);
		shader.SetMat4f("model", &mModel[0][0]);
		shader.SetMat4f("projection", &mProjection[0][0]);
		shader.SetMat4f("prevProj", &mPrevProj[0][0]);

		glBindVertexArray(mVertObj.mVao);
		glBindTexture(GL_TEXTURE_2D, mVertObj.mTex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void GameMap::Update(GAMEEVNET handle)
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		/*
		if (state[SDL_SCANCODE_I]) { MoveCamera(UP);	}
		if (state[SDL_SCANCODE_K]) { MoveCamera(DOWN);	}
		if (state[SDL_SCANCODE_J]) { MoveCamera(LEFT);	}
		if (state[SDL_SCANCODE_L]) { MoveCamera(RIGHT); }
		*/
	}

	void GameMap::CachPrev()
	{
		mPrevProj = mProjection;
	}

	void GameMap::SetCamera(const glm::mat4 &camera)
	{
		mCamera = camera;
		mProjection = camera;
		mPrevProj = camera;
	}

	void GameMap::SetCameraSpeed(float deltX, float deltY)
	{
		mDeltX = deltX;
		mDeltY = deltY;
	}

	void GameMap::MoveCamera(RollDirection direction)
	{
		switch (direction) {
		case UP:	mRun = glm::translate(mRun, glm::vec3(0, mDeltY, 0.0f));	break;
		case DOWN:	mRun = glm::translate(mRun, glm::vec3(0, -mDeltY, 0.0f));	break;
		case LEFT:	mRun = glm::translate(mRun, glm::vec3(-mDeltX, 0.0f, 0.0f));break;
		case RIGHT: mRun = glm::translate(mRun, glm::vec3(mDeltX, 0.0f, 0.0f)); break;
		default: break;
		}

		mProjection = mCamera * mRun;

		// ¼ÆËãÎ»ÖÃ
		mPosition = -mRun * mStartPos;
	}

	void GameMap::MarginMove(
		const glm::vec4 &position, float deltX, float deltY, float disX, float disY)
	{
		mDeltX = deltX;
		mDeltY = deltY;

		if (position.x > mPosition.x + mSize.mX - disX) { 
			MoveCamera(LEFT); 
		}

		if (position.x < mPosition.x + disX) { 
			MoveCamera(RIGHT); 
		}

		if (position.y > mPosition.y + mSize.mY - disY) { 
			MoveCamera(DOWN); 

			LOG_INFO("Down map x = %f, y = %f, tank x = %f, y = %f size y= %f\n",
				mPosition.x, mPosition.y, position.x, position.y, mSize.mY);
		}

		if (position.y < mPosition.y + disY) { 
			MoveCamera(UP); 

			LOG_INFO("Up map x = %f, y = %f, tank x = %f, y = %f\n", 
				mPosition.x, mPosition.y, position.x, position.y);
		}
	}

	void GameMap::Initialize()
	{
		float vertex[24] = {
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,

			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f
		};

		TexInfo info = GenTexInfo("res/back-desert.jpg");

		mVertObj.mTex = info.mTex;

		GameObject::LoadVertex(vertex, sizeof(vertex) / sizeof(float));
		GameObject::Initialize();

		if (!GameObject::IsVertexObjExist(MAP_TYPE)) {
			GameObject::AddVertexObj(MAP_TYPE, mVertObj);
		}
	}

	void GameMap::Terminate()
	{
		GameObject::Terminate();
	}
}
