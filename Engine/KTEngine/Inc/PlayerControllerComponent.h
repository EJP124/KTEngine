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
		Vector3 speed = { 0,0,500 };
	};
}
