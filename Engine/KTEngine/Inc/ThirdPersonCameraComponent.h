#pragma once


#include "Component.h"

namespace KTEngine
{
	class CameraComponent;

	class ThirdPersonCameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::ThirdPersonCamera);

		void Initialize() override;
		void Terminate() override;
		void DebugUI() override;
		void Update(float deltaTime) override;

	private:
		CameraComponent* mCameraComponent = nullptr;
		GameObject* mPlayer = nullptr;
		Graphics::Camera mCamera;
	};
}