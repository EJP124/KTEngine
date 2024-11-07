#include "GameState.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;
using namespace KTEngine::Audio;

void GameState::Initialize()
{
	mGameWorld.AddService<CameraService>();
	mGameWorld.Initialize();

	GameObject* gameObject = mGameWorld.CreateGameObject("Object0");
	//add components first
	gameObject->AddComponent<TransformComponent>();
	//finally initialize
	gameObject->Initialize();

	GameObject* cameraGameObject = mGameWorld.CreateGameObject("Camera");
	cameraGameObject->AddComponent<CameraComponent>();
	cameraGameObject->AddComponent<FPSCameraComponent>();
	cameraGameObject->Initialize();
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		mGameWorld.DebugUI();
	ImGui::End();
}





