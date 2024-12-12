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

	private:
		CameraComponent* mCameraComponent = nullptr;
		TransformComponent* mPlayerTransform =nullptr;
		Vector3 cameraPosOffset = Vector3{ 0, 2, -5 };
		float cameraLookOffset = -1.0f;
	};
}