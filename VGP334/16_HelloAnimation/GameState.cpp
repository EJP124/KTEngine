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

	std::filesystem::path shaderFilePath = (L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureManager::Get()->LoadTexture("misc/basketball.jpg");

	Mesh ground = MeshBuilder::CreateHorizontalPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");

	mAnimationTime = 0.0f;

	mAnimation = AnimationBuilder()
		.AddPositionKey({ 0.0f, 0.5f, 0.0f }, 0.0f)
		.AddPositionKey({ 0.0f, 3.0f, 0.0f }, 2.0f, EaseType::EaseOutQuad)
		.AddPositionKey({ 0.0f, 0.5f, 0.0f }, 4.0f, EaseType::EaseInQuad)
		//.AddRotationKey({ 0.0f, 0.0f, 0.0f, 1.0 }, 0.0f)
		//.AddRotationKey({ -3.141592f, 0.0f, 0.0f, 0.0 }, 3.0f)
		//.AddRotationKey({ 0.0f, 0.0f, 0.0f, 1.0 }, 0.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 0.0f)
		.AddScaleKey({ 0.9f, 2.0f, 0.9f }, 0.25f)
		.AddScaleKey({ 1.0f, 0.5f, 1.0f }, 1.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 3.5f)
		.AddScaleKey({ 1.2f, 0.5f, 1.2f }, 3.75f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 4.0f)
		.Build();

}

void GameState::Terminate()
{
	mBall.Terminate();
	mGround.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCameraControl(deltaTime);
	//update the animation
	mAnimationTime += deltaTime;
	while (mAnimationTime > mAnimation.GetDuration())
	{
		mAnimationTime -= mAnimation.GetDuration();
	}
	//if duration is 1sec
	//if animationTime is at 0.9
	//deltaTime is 0.2
	//animationTime = 1.1
	//correct loop 1.1 - 1 = 0.1
	//wrong/old loop 1.1 = 0.0
}

void GameState::Render()
{
	mBall.transform = mAnimation.GetTransform(mAnimationTime);
	SimpleDraw::Render(mCamera);
	mStandardEffect.Begin();
		mStandardEffect.Render(mBall);
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
