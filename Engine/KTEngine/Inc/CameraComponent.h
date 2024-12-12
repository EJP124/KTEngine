#pragma once

#include "Component.h"

namespace KTEngine
{
	enum class CameraType
	{
		FPSCamera,
		ThirdPersonCamera
	};

	class CameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::Camera);

		void Initialize() override;
		void Terminate() override;
		void DebugUI() override;
		void Update(float deltaTime) override;
		void Serialize(rapidjson::Document& doc, rapidjson::Value& value) override;
		void Deserialize(const rapidjson::Value& value) override;

		Graphics::Camera& GetCamera();
		const Graphics::Camera& GetCamera() const;
		const CameraType GetCameraType() const;

	private:
		Graphics::Camera mCamera;
		CameraType cType = CameraType::FPSCamera;
	};
}