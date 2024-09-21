#include "GameState.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;
using namespace KTEngine::Audio;
using namespace KTEngine::Physics;

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

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.1f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureManager::Get()->LoadTexture("misc/basketball.jpg");

	Mesh ground = MeshBuilder::CreateHorizontalPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");

	ModelManager* mm = ModelManager::Get();
	//create shape
	mModelId = mm->LoadModelId("../../Assets/Models/Character03/MutantRightTurn45.model");
	mm->AddAnimation(mModelId, "../../Assets/Models/Character05/Victory.animset");
	mCharacter = CreateRenderGroup(mModelId, &mCharacterAnimator);
	mCharacterAnimator.Initialize(mModelId);

	mModelId1 = mm->LoadModelId("../../Assets/Models/Character04/Capoeira.model");
	mm->AddAnimation(mModelId1, "../../Assets/Models/Character06/DancingTwerk.animset");
	mCharacter1 = CreateRenderGroup(mModelId1, &mCharacterAnimator1);
	mCharacterAnimator1.Initialize(mModelId1);

	mAnimationTime = 0.0f;
	BallAnimation();
	Animation1();
	Animation2();
	
	ParticleEffect();
}

void GameState::BallAnimation()
{
	SoundEffectManager* sem = SoundEffectManager::Get();
	mSoundEventIds.push_back(sem->Load("photongun1.wav"));
	mSoundEventIds.push_back(sem->Load("explosion.wav"));
	AnimationCallback cb = [&]() {SoundEffectManager::Get()->Play(mSoundEventIds[0]); };
	//4.5 is the maxHeight 0.5 is the minHeight
	mAnimation = AnimationBuilder()
		.AddPositionKey({ 5.0f, 0.5f, 5.0f }, 0.0f)
		.AddPositionKey({ -5.0f, 1.0f, -5.0f }, 5.0f)
		.AddPositionKey({ 5.0f, 2.0f, -3.0f }, 9.5f)
		.AddPositionKey({ -5.0f, 4.0f, -0.0f }, 15.0f)
		.AddPositionKey({ -4.0f, 4.5f, 2.0f }, 15.7f)
		.AddPositionKey({ 5.0f, 1.0f, 4.0f }, 19.7f)
		.AddPositionKey({ 4.0f, 0.5f, 1.0f }, 20.3f)
		.AddPositionKey({ -5.0f, 2.0f, -3.0f }, 23.8f)
		.AddPositionKey({ 5.0f, 4.0f, -5.0f }, 27.3f)
		.AddPositionKey({ 4.8f, 4.5f, 0.5f }, 27.5f)
		.AddPositionKey({ 2.8f, 0.5f, 3.5f }, 28.5f)
		.AddPositionKey({ -1.0f, 5.0f, 5.0f }, 30.0f)
		.AddPositionKey({ -5.0f, 3.0f, 3.0f }, 31.5f)
		.AddPositionKey({ 0.0f, 0.5f, 2.5f }, 33.0f)
		.AddPositionKey({ 5.0f, 3.5f, 0.0f }, 34.3f)
		.AddPositionKey({ 1.0f, 4.5f, 4.0f }, 35.3f)
		.AddPositionKey({ -5.0f, 2.8f, 0.0f }, 36.5f)
		.AddPositionKey({ 3.0f, 0.5f, 2.0f }, 37.5f)
		.AddPositionKey({ 5.0f, 3.0f, 5.0f }, 38.0f)
		.AddPositionKey({ 4.0f, 4.5f, 3.0f }, 38.5f)
		.AddPositionKey({ -2.0f, 0.5f, 1.0f }, 39.0f)
		.AddPositionKey({ -5.0f, 1.5f, 2.0f }, 39.2f)
		.AddPositionKey({ 4.0f, 4.5f, 5.0f }, 39.7f)
		.AddPositionKey({ 4.0f, 0.0f, 5.0f }, 40.0f)
		.AddPositionKey({ 10000000.0f, 0.0f, 5000000.0f }, 45.0f)
		.AddRotationKey({ 0.0f, 0.0f, 0.0f, 1.0 }, 0.0f)
		.AddRotationKey({ 0.0f, 3.141592f, 0.0f, 1.0 }, 40.7f)
		.AddEventKey(cb, 0.1f)
		.AddEventKey(std::bind(&GameState::OnEvent, this), 40.0f)
		.Build();
}

void GameState::OnEvent()
{
	SoundEffectManager::Get()->Play(mSoundEventIds[1]);
	AnimEvent animEvent;
	animEvent.eventName = "Explode";
	EventManager::Broadcast(&animEvent);
}

void GameState::Animation1()
{
	AnimationCallback cb = [&]() { mCharacterAnimator.PlayAnimation(0, true); };
	mAnimation1 = AnimationBuilder()
		.AddPositionKey({ 0.0f, 0.0f, 0.0f }, 0.0f)
		.AddPositionKey({ 3.0f, 0.0f, 0.0f }, 10.0f)
		.AddPositionKey({ 3.0f, 0.0f, 4.0f }, 20.0f)
		.AddPositionKey({ 5.0f, 0.0f, 0.0f }, 30.0f)
		.AddPositionKey({ -3.0f, 0.0f, -2.0f }, 40.0f)
		.AddRotationKey({ 0.0f, 0.0f, 0.0f, 1.0f }, 0.0f)
		.AddRotationKey({ 0.0f, 3.0f, 0.0f, 0.0f }, 45.0f)
		.AddEventKey(cb, 0.1f)
		.AddEventKey([&]() { mCharacterAnimator.PlayAnimation(1, true); }, 40.0f)
		.Build();
}

void GameState::Animation2()
{
	AnimationCallback cb = [&]() {mCharacterAnimator1.PlayAnimation(0, true); };
	mAnimation2 = AnimationBuilder()
		.AddPositionKey({ 0.0f, 0.0f, 0.0f }, 0.0f)
		.AddPositionKey({ -3.0f, 0.0f, 2.0f }, 10.0f)
		.AddPositionKey({ 3.0f, 0.0f, -2.0f }, 20.0f)
		.AddPositionKey({ -5.0f, 0.0f, 2.0f }, 30.0f)
		.AddPositionKey({ 4.0f, 0.0f, 5.0f }, 40.0f)
		.AddEventKey(cb, 0.1f)
		.AddEventKey([&]() { mCharacterAnimator1.PlayAnimation(1, true); }, 20.0f)
		.Build();

	
}

void GameState::ParticleEffect()
{
	mParticleEffect.Initialize();
	mParticleEffect.SetCamera(mCamera);

	ParticleSystemInfo info;
	info.maxParticles = 100;
	info.particleTextureId = TextureManager::Get()->LoadTexture("Images/fire.png");
	info.spawnPosition = Math::Vector3::Zero;
	info.spawnDirection = Math::Vector3::YAxis;
	info.spawnDelay = 0.0f;
	info.spawnLifeTime = 99999999999999.0f;
	info.minParticlePerEmit = 3;
	info.maxParticlePerEmit = 5;
	info.minTimeBetweenEmit = 0.05f;
	info.maxTimeBetweenEmit = 0.1f;
	info.minSpawnAngle = -30.0f * Math::Constants::Pi / 180.0f;
	info.maxSpawnAngle = 30.0f * Math::Constants::Pi / 180.0f;
	info.minSpeed = 2.0f;
	info.maxSpeed = 5.0f;
	info.minParticleLifeTime = 0.5f;
	info.maxParticleLifeTime = 1.0f;
	info.minStartColor = Colors::Red;
	info.maxStartColor = Colors::Yellow;
	info.minEndColor = Colors::White;
	info.maxEndColor = Colors::Orange;
	info.minStartScale = Math::Vector3::One;
	info.maxStartScale = { 1.5f, 1.5f, 1.5f };
	info.minEndScale = { 0.05f, 0.05f, 0.05f };
	info.maxEndScale = { 0.1f, 0.1f, 0.1 };
	mParticleSystem.Initialize(info);
	mParticleSystem.SetCamera(mCamera);
	mParticleSystem.SetPosition({ 4.0f, 1.0f, 5.0f });
}

void GameState::Terminate()
{
	mBall.Terminate();
	mGround.Terminate();
	mStandardEffect.Terminate();
	mParticleSystem.Terminate();
	mParticleEffect.Terminate();
	CleanupRenderGroup(mCharacter);
	CleanupRenderGroup(mCharacter1);
}

void GameState::Update(float deltaTime)
{
	UpdateCameraControl(deltaTime);
	mCharacterAnimator.Update(deltaTime);
	mCharacterAnimator1.Update(deltaTime);
	mParticleSystem.Update(deltaTime);
	//update the animation
	float prevTime = mAnimationTime;
	mAnimationTime += deltaTime;
	mAnimation.PlayEvents(prevTime, mAnimationTime);
	mAnimation1.PlayEvents(prevTime, mAnimationTime);
	mAnimation2.PlayEvents(prevTime, mAnimationTime);
	while (mAnimationTime > mAnimation.GetDuration())
	{
		mAnimationTime -= mAnimation.GetDuration();
	}
}

void GameState::Render()
{
	for (auto& ro : mCharacter)
	{
		ro.transform = mAnimation1.GetTransform(mAnimationTime);
	}
	for (auto& ro : mCharacter1)
	{
		ro.transform = mAnimation2.GetTransform(mAnimationTime);
	}
	if (mDrawSkeleton)
	{
		AnimationUtil::BoneTransforms bonTransforms;
		AnimationUtil::ComputeBoneTransforms(mModelId, bonTransforms, &mCharacterAnimator);
		AnimationUtil::DrawSkeleton(mModelId, bonTransforms);
	}
	if (mAnimationTime >= 40.0f)
	{
		mParticleEffect.Begin();
			mParticleSystem.Render(mParticleEffect);
		mParticleEffect.End();
	}
	
	
	mBall.transform = mAnimation.GetTransform(mAnimationTime);
	SimpleDraw::Render(mCamera);
	mStandardEffect.Begin();
		mStandardEffect.Render(mBall);
		mStandardEffect.Render(mGround);
		DrawRenderGroup(mStandardEffect, mCharacter);
		if (mAnimationTime < 40.0f)
		{
			DrawRenderGroup(mStandardEffect, mCharacter1);
		}
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
	ImGui::Checkbox("DrawSkeleton", &mDrawSkeleton);
	
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
	if (input->IsKeyDown(KeyCode::SPACE))
	{
		mAnimationTime += 0.01;
	}
}
