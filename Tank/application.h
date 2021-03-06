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

		// 创建窗口
		void CreateWindow(const char *title);

		// 加载 Opengl api
		void LoadGraphicApi();

		// 渲染
		void Render();

	protected:

		// 主窗口句柄
		WINDOWHANDLE mainWindow;

		// 主窗口上下文
		OPENGLCONTEXT mainContext;

		// 窗口的尺寸
		int winWidth;
		int winHeight;

		// 逻辑帧和渲染帧的值
		int defRenderFps;
		int defLogicFps;

		Game mGame;
	};
}


#endif // __APPLICATION_H__
