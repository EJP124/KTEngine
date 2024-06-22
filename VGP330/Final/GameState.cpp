#include "GameState.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f,0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f, 0.8f, 0.1f };
	mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	//create shape
	Model model;
	ModelIO::LoadModel("../../Assets/Models/Character01/Mutant.fbx", model);
	ModelIO::LoadMaterial("../../Assets/Models/Character01/Mutant.fbx", model);
	mCharacter = CreateRenderGroup(model);

	Mesh sphere = MeshBuilder::CreateSphere(20, 20, 0.5);
	mBall.meshBuffer.Initialize(sphere);

	mCameraTarget.SetPosition(mBall.transform.position);
	mCameraTarget.SetLookAt({ mBall.transform.position.x, mBall.transform.position.y , mBall.transform.position.z });
	

	Mesh groundMesh = MeshBuilder::CreateHorizontalPlane(20, 20, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");

	std::filesystem::path shaderFilePath = (L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());
	mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());
	mStandardEffect.SetShadowMapFar(mShadowEffect.GetDepthMap());

	mReflectionEffect.Initialize();
	mReflectionEffect.SetCamera(mCamera);
	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);
	
	fov = 2.5f;
}

void GameState::Terminate()
{
	mStandardEffect.Terminate();
	mGround.Terminate();
	CleanupRenderGroup(mCharacter);
}

void GameState::Update(float deltaTime)
{
	UpdateCameraControl(deltaTime);
	SetRenderGroupPosition(mCharacter, positionSet);
	mCameraTarget.SetPosition(mBall.transform.position);
	Vector3 reDir= Normalize(mCamera.GetPosition() - mCameraTarget.GetPosition());
	mCameraTarget.SetLookAt(reDir);
	mBall.transform.position = positionSetBall;
	mCameraTarget.SetFov(fov);
}

void GameState::Render()
{
	//SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	//SimpleDraw::Render(mCamera);
	
	mStandardEffect.SetCamera(mCameraTarget);
		mReflectionEffect.mTarget.BeginRender();
			mStandardEffect.Begin();
			mStandardEffect.Render(mGround);
				DrawRenderGroup(mStandardEffect, mCharacter);
			mStandardEffect.End();
	mReflectionEffect.mTarget.EndRender();


	mStandardEffect.SetCamera(mCamera);
		
	mReflectionEffect.Begin();
		mReflectionEffect.Render(mBall);
	mReflectionEffect.End();

	mShadowEffect.Begin();
		DrawRenderGroup(mShadowEffect, mCharacter);
	mShadowEffect.End();

	mStandardEffect.Begin();
		DrawRenderGroup(mStandardEffect, mCharacter);
		
		mStandardEffect.Render(mGround);
	mStandardEffect.End();

}
void GameState::DebugUI()
{
	ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
		{
			mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
		}
		ImGui::DragFloat3("Position", &positionSet.x, 0.01f);
		ImGui::DragFloat3("Position2", &positionSetBall.x, 0.01f);
		ImGui::DragFloat("FOV", &fov, 0.01f);
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	mStandardEffect.DebugUI();

	ImGui::End();
}

void GameState::UpdateCameraControl(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}
