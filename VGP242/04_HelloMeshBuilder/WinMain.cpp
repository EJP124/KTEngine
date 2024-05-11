#include <KTEngine/Inc/KTEngine.h>

#include "GameState.h"

using namespace KTEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Cube";

	App& myApp = MainApp();
	myApp.AddState<SkySphere>("StateOne");
	myApp.AddState<GroundPlane>("StateTWO");
	myApp.AddState<Cube>("StateTHREE");
	myApp.AddState<PyramidPC>("StateFOUR");
	myApp.AddState<SkyBox>("StateFIVE");
	myApp.AddState<SpherePC>("StateSIX");
	myApp.AddState<CylinderPC>("StateSEVEN");
	myApp.Run(config);

	return(0);
}