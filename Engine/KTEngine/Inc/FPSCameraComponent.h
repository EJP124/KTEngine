#pragma once


#include "Component.h"

namespace KTEngine
{
	class CameraComponent;
	class TransformComponent;

	class FPSCameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::FPSCamera);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;

		void Serialize(rapidjson::Document& doc, rapidjson::Value& value) override;

	private:
		CameraComponent* mCameraComponent = nullptr;
		TransformComponent* mPlayerTransform = nullptr;
	};
}