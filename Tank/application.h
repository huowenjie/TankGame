#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "global.h"

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

		// ���ڵĳߴ�
		int winWidth;
		int winHeight;
	};
}


#endif // __APPLICATION_H__
