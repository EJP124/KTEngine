#include <KTEngine/Inc/KTEngine.h>

#include "GameState.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{

	App& myApp = KTEngine::MainApp();
	myApp.AddState<GameState>("GameState");

	AppConfig config;
	config.appName = L"Hello GameObject";

	myApp.Run(config);

	return(0);
}