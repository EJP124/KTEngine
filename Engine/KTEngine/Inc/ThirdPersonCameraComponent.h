#pragma once


#include "Component.h"

namespace KTEngine
{
	class CameraComponent;
	class TransformComponent;
	class RigidBodyComponent;

	class ThirdPersonCameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::ThirdPersonCamera);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
		void Serialize(rapidjson::Document& doc, rapidjson::Value& value) override;

	private:
		CameraComponent* mCameraComponent = nullptr;
		TransformComponent* mPlayerTransform =nullptr;
		Vector3 cameraPositionOffset = Vector3{ 0, 2, 0 };
		float cameraPosOffset = 3.0f;
		float cameraLookOffset = -0.3f;
		float cameraSpeed = 1.6f;
		float cameraLookSpeed = 1.6f;
	};
}