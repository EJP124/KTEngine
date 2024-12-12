#include "Precompiled.h"
#include "ThirdPersonCameraComponent.h"

#include "GameObject.h"
#include "SaveUtil.h"

#include "TransformComponent.h"

#include "CameraComponent.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;

void ThirdPersonCameraComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "FPSCameraComponent: Camera not found");

	mPlayerTransform = GetOwner().GetComponent<TransformComponent>();
}
void ThirdPersonCameraComponent::Terminate()
{
	mCameraComponent = nullptr;
}
void ThirdPersonCameraComponent::Update(float deltaTime)
{
	if (mCameraComponent->GetCameraType() == CameraType::ThirdPersonCamera)
	{
		Camera& camera = mCameraComponent->GetCamera();
		Vector3 targetPosition = mPlayerTransform->position + cameraPosOffset;
		Vector3 cameraPosition = Lerp(camera.GetPosition(), targetPosition, 0.6 * deltaTime);

		camera.SetPosition(cameraPosition);

		Vector3 LookDir = Lerp(camera.GetDirection(), Vector3(0, cameraLookOffset, mPlayerTransform->position.z), 0.6*deltaTime);
		Normalize(LookDir);
		camera.SetDirection(LookDir);
		
		
	}
	//camera.SetPosition(parent->GetComponent<TransformComponent>()->position);
	// vector3 targetPosition = transformComponent + offset
	// vector3 cameraPosition = Lerp(camera->getposition(), targetPosition, 0.6 * deltaTime)
	// camera.setposition(cameraPosition)
	// camera.setlookat(transformComponent + lookoffset) or camer.setLookat(look direction)
}

void ThirdPersonCameraComponent::DebugUI()
{
}