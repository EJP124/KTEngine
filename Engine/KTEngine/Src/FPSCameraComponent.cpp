#include "Precompiled.h"
#include "FPSCameraComponent.h"

#include "GameObject.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "SaveUtil.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;

void FPSCameraComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "FPSCameraComponent: Camera not found");

	mPlayerTransform = GetOwner().GetComponent<TransformComponent>();
	ASSERT(mCameraComponent != nullptr, "FPSCameraComponent: Transform not found");
}

void FPSCameraComponent::Terminate()
{
	mCameraComponent = nullptr;
	mPlayerTransform = nullptr;
}

void FPSCameraComponent::Update(float deltaTime)
{
	if (mCameraComponent->GetCameraType() == CameraType::FPSCamera)
	{
		Camera& camera = mCameraComponent->GetCamera();
		Matrix4 matWorld = mPlayerTransform->GetMatrix4();
		camera.SetPosition(mPlayerTransform->position + Math::GetLook(matWorld));
		
		Vector3 LookDir = Math::GetLook(matWorld);
		Normalize(LookDir);
		camera.SetDirection(LookDir);

	}
	
}


