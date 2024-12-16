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

void FPSCameraComponent::Serialize(rapidjson::Document& doc, rapidjson::Value& value)
{
	Camera& mCamera = mCameraComponent->GetCamera();
	rapidjson::Value componentValue(rapidjson::kObjectType);
	SaveUtil::SaveVector3("Position", mCamera.GetPosition(), doc, componentValue);
	SaveUtil::SaveVector3("LookAt", mCamera.GetPosition() + mCamera.GetDirection(), doc, componentValue);
	value.AddMember("FPSCameraComponent", componentValue, doc.GetAllocator());
}


