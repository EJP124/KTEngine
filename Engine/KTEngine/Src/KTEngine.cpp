#include "Precompiled.h"
#include "KTEngine.h"

KTEngine::App& KTEngine::MainApp()
{
	static App sApp;
	return sApp;
}