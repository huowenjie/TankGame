#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "game.h"

namespace hwj
{
	class Tank;
	class Application 
	{
	public:
		Application();
		Application(int width, int height);
		~Application();

	public:

		// ��������
		void CreateWindow(const char *title);

		// ���� Opengl api
		void LoadGraphicApi();

		// ��Ⱦ
		void Render();

	protected:

		// �����ھ��
		WINDOWHANDLE mainWindow;

		// ������������
		OPENGLCONTEXT mainContext;

		// ���ڵĳߴ�
		int winWidth;
		int winHeight;

		// �߼�֡����Ⱦ֡��ֵ
		int defRenderFps;
		int defLogicFps;

		Game mGame;
	};
}


#endif // __APPLICATION_H__
