#include "application.h"

int main(int argc, char *argv[])
{
	using namespace hwj;

	Application app;

	app.CreateWindow("Tank");
	app.LoadGraphicApi();
	app.Render();

	return 0;
}


