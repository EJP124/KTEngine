#include "Precompiled.h"
#include "ThirdPersonCameraComponent.h"

#include "GameObject.h"
#include "CameraComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "SaveUtil.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;

void ThirdPersonCameraComponent::Initialize()
{

	mCameraComponent = GetOwner().GetComponent<CameraComponent>();
	ASSERT(mCameraComponent != nullptr, "FPSCameraComponent: Camera not found");

	
}
void ThirdPersonCameraComponent::Terminate()
{
	mCameraComponent = nullptr;
}
void ThirdPersonCameraComponent::Update(float deltaTime)
{
	Camera& camera = mCameraComponent->GetCamera();

}

void ThirdPersonCameraComponent::DebugUI()
{
	Vector3 pos = mCamera.GetPosition();
	ImGui::Text("Position", &pos);
}