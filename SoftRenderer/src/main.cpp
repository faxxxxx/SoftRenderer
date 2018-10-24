#include "Core/App/Application.h"

const int ScreenWidth = 450;
const int ScreenHeight = 450;

int main(int argc, char** argv) {
	Application app;
	if (app.Init(ScreenWidth, ScreenHeight)) {
		app.Run();
	}
	return 0;
}
