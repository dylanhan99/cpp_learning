#include "nepch.h"
#include "Core/Application.h"

int main() {

	NoobEngine::Core::Application app;
	app.Init();
	app.Update();
	app.Terminate();

	return 0;
}
