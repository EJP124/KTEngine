#include "GameState.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;
using namespace KTEngine::Audio;



void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f,0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f,0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f, 0.8f, 0.1f };
	mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	//create shape
	mModelId = ModelManager::Get()->LoadModelId("../../Assets/Models/Character03/MutantRightTurn45.model");
	mCharacter = CreateRenderGroup(mModelId, &mCharacterAnimator);
	mCharacterAnimator.Initialize(mModelId);

	std::filesystem::path shaderFilePath = (L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.Initialize(shaderFilePath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	SoundEffectManager* sem = SoundEffectManager::Get();
	mSoundEventIds.push_back(sem->Load("megamanx_blast.wav"));
	mSoundEventIds.push_back(sem->Load("photongun1.wav"));
	mSoundEventIds.push_back(sem->Load("explosion.wav"));

	AnimationCallback cb = [&]() {SoundEffectManager::Get()->Play(mSoundEventIds[0]); };
	mEventAnimationTime = 0.0f;
	mEventAnimation = AnimationBuilder()
		.AddPositionKey({ 0.0f, 0.0f, 0.0f }, 0.0f)
		.AddPositionKey({ 3.0f, 0.0f, 0.0f }, 2.0f)
		.AddPositionKey({ 0.0f, 0.0f, 0.0f }, 3.0f)
		.AddEventKey(cb, 1.0f)
		.AddEventKey(std::bind(&GameState::OnEvent2,this), 2.0f)
		.AddEventKey(std::bind(&GameState::OnEvent3, this), 3.0f)
		.Build();

	EventManager* em = EventManager::Get();
	mSpaceEventId = em->AddListener(EventType::SpacePressed, std::bind(&GameState::OnSpaceEvent, this, std::placeholders::_1));
	mAnimEventId = em->AddListener(EventType::AnimEvent, std::bind(&GameState::OnAnimEvent, this, std::placeholders::_1));

}

void GameState::Terminate()
{
	mStandardEffect.Terminate();
	CleanupRenderGroup(mCharacter);
}

void GameState::Update(float deltaTime)
{
	mCharacterAnimator.Update(deltaTime);
	UpdateCameraControl(deltaTime);

	float prevTime = mEventAnimationTime;
	mEventAnimationTime += deltaTime;
	mEventAnimation.PlayEvents(prevTime, mEventAnimationTime);
	while (mEventAnimationTime >= mEventAnimation.GetDuration())
	{
		mEventAnimationTime -= mEventAnimation.GetDuration();
	}
}

void GameState::Render()
{
	for (auto& ro : mCharacter)
	{
		ro.transform = mEventAnimation.GetTransform(mEventAnimationTime);
	}
	if (mDrawSkeleton)
	{
		AnimationUtil::BoneTransforms bonTransforms;
		AnimationUtil::ComputeBoneTransforms(mModelId, bonTransforms, &mCharacterAnimator);
		AnimationUtil::DrawSkeleton(mModelId, bonTransforms);
	}
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);
	if (!mDrawSkeleton)
	{
		mStandardEffect.Begin();
		DrawRenderGroup(mStandardEffect, mCharacter);
		mStandardEffect.End();
	}

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
	if (ImGui::DragInt("Animation", &mAnimIndex, 1, -1, mCharacterAnimator.GetAnimationCount() - 1))
	{
		mCharacterAnimator.PlayAnimation(mAnimIndex, true);
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

	//if character1 and character1 overlap
	// ContactEvent contactEvent;
	//	contactEvent.objA = character1
	//	contactEvent.objB = character2
	//EventManger::Broadcast(contactEvent)
	if (input->IsKeyPressed(KeyCode::SPACE))
	{
		SpacePressedEvent spacePressed;
		EventManager::Broadcast(&spacePressed);
	}
}

void GameState::OnEvent2()
{
	SoundEffectManager::Get()->Play(mSoundEventIds[1]);
	AnimEvent animEvent;
	animEvent.eventName = "Shoot";
	EventManager::Broadcast(&animEvent);
}

void GameState::OnEvent3()
{
	SoundEffectManager::Get()->Play(mSoundEventIds[2]);
	AnimEvent animEvent;
	animEvent.eventName = "Explode";
	EventManager::Broadcast(&animEvent);
}


void GameState::OnSpaceEvent(const KTEngine::Event* event)
{
	LOG("SPACE EVENT OCCURED");
	SoundEffectManager::Get()->Play(mSoundEventIds[2]);
}
void GameState::OnAnimEvent(const KTEngine::Event* event)
{
	AnimEvent* eventData = (AnimEvent*)event;
	if (eventData->eventName == "Shoot")
	{
		LOG("SHOOT EVENT OCCURED");
	}
	else if (eventData->eventName == "Explode")
	{
		LOG("EXPLODE EVENT OCCURED");
	}
}

