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
}

void FPSCameraComponent::Terminate()
{
	mCameraComponent = nullptr;
}

void FPSCameraComponent::Update(float deltaTime)
{
	if (mCameraComponent->GetCameraType() == CameraType::FPSCamera)
	{
		Camera& camera = mCameraComponent->GetCamera();
		Vector3 targetPosition = mPlayerTransform->position;
		Vector3 cameraPosition = Lerp(camera.GetPosition(), targetPosition, 0.8 * deltaTime);

		camera.SetPosition(cameraPosition);

		Vector3 LookDir = Lerp(camera.GetDirection(), Vector3(0, 0, mPlayerTransform->position.z), 0.6 * deltaTime);
		Normalize(LookDir);
		camera.SetDirection(LookDir);

	}
	
}


