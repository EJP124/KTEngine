#include "GameState.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Math;
using namespace KTEngine::Input;
using namespace KTEngine::Colors;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f,0.0f });

	mMesh = MeshBuilder::CreateSpherePX(100, 100, 1.0f);
	mRenderObject.meshBuffer.Initialize(mMesh);
	mRenderObject.transform.position.x = 3.0f;

	

	std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoTexturing.fx";
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
}

void GameState::Terminate()
{
	mStandardEffect.Terminate();
	mRenderObject.Terminate();
}

void GameState::Update(float deltaTime)
{
	
}

void GameState::Render()
{
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);
	mStandardEffect.Begin();
		mStandardEffect.Render(mRenderObject);
	mStandardEffect.End();
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mStandardEffect.DebugUI();
	ImGui::End();
}

