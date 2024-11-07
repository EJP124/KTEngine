#include "Precompiled.h"
#include "App.h"
#include "AppState.h"
#include "EventManager.h"

using namespace KTEngine;
using namespace KTEngine::Core;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;
using namespace KTEngine::Physics;
using namespace KTEngine::Audio;

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}

void App::Run(const AppConfig& config)
{
	LOG("App Started: %.3f",TimeUtil::GetTime());

	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	ASSERT(myWindow.IsActive(), "Failed to create a window");
	auto handle = myWindow.GetWindowHandle();
	GraphicsSystem::StaticInitialize(myWindow.GetWindowHandle(), false);
	InputSystem::StaticInitialize(handle);
	DebugUI::StaticInitialize(handle, false, true);
	SimpleDraw::StaticInitialize(config.maxVertexCount);
	TextureManager::StaticInitialize("../../Assets/Textures");
	ModelManager::StaticInitialize();
	AudioSystem::StaticInitialize();
	SoundEffectManager::StaticInitialize("../../Assets/Sounds");
	EventManager::StaticInitialize();

	PhysicsWorld::Settings settings;
	PhysicsWorld::StaticInitialize(settings);

	ASSERT(mCurrentState != nullptr, "App: need an app state");
	mCurrentState->Initialize();

	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();

		InputSystem* input = InputSystem::Get();
		input->Update();

		if (!myWindow.IsActive() || input->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			break;
		}

		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		AudioSystem::Get()->Update();

		float deltaTime = TimeUtil::GetDeltaTime();
		if (deltaTime < 0.5f)
		{
#ifndef USE_PHYSICS_SERVICE
			PhysicsWorld::Get()->Update(deltaTime);
#endif 
			mCurrentState->Update(deltaTime);
		}
		GraphicsSystem* gs = GraphicsSystem::Get();
		gs->BeginRender();
			mCurrentState->Render();
			DebugUI::BeginRender();
				mCurrentState->DebugUI();
			DebugUI::EndRender();
		gs->EndRender();
	}

	mCurrentState->Terminate();

	EventManager::StaticTerminate();
	SoundEffectManager::StaticTerminate();
	AudioSystem::StaticTerminate();
	PhysicsWorld::StaticTerminate();
	ModelManager::StaticTerminate();
	TextureManager::StaticTerminate();
	SimpleDraw::StaticTerminate();
	DebugUI::StaticTerminate();
	InputSystem::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	myWindow.Terminate();
}

void App::Quit()
{
	mRunning = false;
}