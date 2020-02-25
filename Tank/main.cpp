#include "application.h"

#pragma comment(lib, "glad.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

int main(int argc, char *argv[])
{
	using namespace hwj;

	Application app;

	app.CreateWindow("Tank");
	app.LoadGraphicApi();
	app.Render();

	return 0;
}
