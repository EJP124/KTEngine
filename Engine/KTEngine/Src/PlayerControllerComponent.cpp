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
	if (mPlayerRb != nullptr)
	{
		if (input->IsKeyDown(KeyCode::W))
		{	
			force = 200.0f * deltaTime;
		}
		else if (input->IsKeyDown(KeyCode::S))
		{
			if (force <= 0)
			{
				force = 0;
			}
			else
			{
				force -= (friction + brakeForce) * deltaTime;
			}

		}
		else
		{
			if (force <= 0)
			{
				force = 0;
			}
			else
			{
				force -= friction * deltaTime;
			}
		}

		if (mPlayerRb->GetVelocity() > 0.01)
		{
			if (input->IsKeyDown(KeyCode::A))
			{
				turnAngle = { 0, -2, 0 };
			}
			else if (input->IsKeyDown(KeyCode::D))
			{
				turnAngle = { 0, 2, 0 };
			}
			else
			{
				turnAngle = Vector3::Zero;
			}
		}
		else
		{
			turnAngle = Vector3::Zero;
		}

		mPlayerRb->SetAngularVelocity(turnAngle);
		Matrix4 matWorld = mTransformComponent->GetMatrix4();
		mPlayerRb->AddForce(Math::GetLook(matWorld) * force, mTransformComponent->position);
	}
	
	
}






