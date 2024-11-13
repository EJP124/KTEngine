#include "GameState.h"

#include "CustomDebugDrawService.h"
#include "CustomDebugDrawComponent.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;
using namespace KTEngine::Audio;

Component* CustomComponentMake(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomDebugDrawComponent")
	{
		return gameObject.AddComponent<CustomDebugDrawComponent>();
	}
	return nullptr;
}
Component* CustomComponentGet(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomDebugDrawComponent")
	{
		return gameObject.GetComponent<CustomDebugDrawComponent>();
	}
	return nullptr;
}
Service* CustomServiceMake(const std::string& serviceName, GameWorld& gameWorld)
{
	if (serviceName == "CustomDebugDrawService")
	{
		return gameWorld.AddService<CustomDebugDrawService>();
	}
	return nullptr;
}

void GameState::Initialize()
{
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	GameObjectFactory::SetCustomGet(CustomComponentGet);
	GameWorld::SetCustomService(CustomServiceMake);
	mGameWorld.LoadLevel(L"../../Assets/Templates/test_level.json");
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