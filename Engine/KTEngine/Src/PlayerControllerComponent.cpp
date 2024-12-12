#include "Precompiled.h"
#include "PlayerControllerComponent.h"

#include "GameWorld.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;


void PlayerControllerComponent::Initialize()
{
	mPlayerRb = GetOwner().GetComponent<RigidBodyComponent>();

	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void PlayerControllerComponent::Terminate()
{
	mTransformComponent = nullptr;
	mPlayerRb = nullptr;
}

void PlayerControllerComponent::Update(float deltaTime)
{
	auto input = InputSystem::Get();

	
	
	if (input->IsKeyDown(KeyCode::W))
	{
		mPlayerRb->AddForce(speed * deltaTime, mTransformComponent->position);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mPlayerRb->SetVelocity(-speed * deltaTime);
	}

}
