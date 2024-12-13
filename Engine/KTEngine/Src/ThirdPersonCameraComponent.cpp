#include "Precompiled.h"
#include "ThirdPersonCameraComponent.h"

#include "GameObject.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"

#include "CameraComponent.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;

void ThirdPersonCameraComponent::Initialize()
{
	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "ThirdPersonCameraComponent: Camera not found");

	mPlayerTransform = GetOwner().GetComponent<TransformComponent>();
	ASSERT(mCameraComponent != nullptr, "ThirdPersonCameraComponent: Camera not found");
	
}
void ThirdPersonCameraComponent::Terminate()
{
	mCameraComponent = nullptr;
	mPlayerTransform = nullptr;
}
void ThirdPersonCameraComponent::Update(float deltaTime)
{
	if (mCameraComponent->GetCameraType() == CameraType::ThirdPersonCamera)
	{
		Camera& camera = mCameraComponent->GetCamera();
		Matrix4 matWorld = mPlayerTransform->GetMatrix4();
		Vector3 targetPosition = mPlayerTransform->position + (Math::GetLook(matWorld) * -cameraPosOffset ) + cameraPositionOffset;
		Vector3 cameraPosition = Lerp(camera.GetPosition(), targetPosition, 1.6 * deltaTime);

		camera.SetPosition(cameraPosition);

		Vector3 LookDir = Lerp(camera.GetDirection(), Math::GetLook(matWorld) + Vector3(0, cameraLookOffset, 0), 1.6 * deltaTime);
		Normalize(LookDir);
		camera.SetDirection(LookDir);
		
		
	}
}
