#pragma once

#include "Component.h"


namespace KTEngine
{
	class RigidBodyComponent;
	class TransformComponent;
	class PlayerControllerComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::PlayerController);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;

	private:

		RigidBodyComponent* mPlayerRb = nullptr;
		TransformComponent* mTransformComponent = nullptr;
		
		Vector3 moveVelocity = Vector3::Zero;
		float force = 0.0f;
		float friction = 30.0f;
		float brakeForce = 200.0f;

		Vector3 turnAngle = Vector3::Zero;
	};
}
