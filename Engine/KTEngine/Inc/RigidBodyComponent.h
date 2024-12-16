#pragma once

#include "Component.h"

namespace KTEngine
{
	class RigidBodyComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::RigidBody);

		void Initialize() override;
		void Terminate() override;
		void DebugUI() override;
		void Serialize(rapidjson::Document& doc, rapidjson::Value& value);
		void Deserialize(const rapidjson::Value& value) override;

		void SetPosition(const Math::Vector3& position);
		void SetVelocity(const Math::Vector3& velocity);
		void AddForce(const Math::Vector3& force, const Math::Vector3& position);
		float GetVelocity();
		void SetAngularVelocity(const Math::Vector3& angularVelocity);
	private:
		friend class PhysicsService;
		Physics::CollisionShape mCollisionShape;
		Physics::RigidBody mRigidBody;
		float mMass = -1.0f;
	};
}