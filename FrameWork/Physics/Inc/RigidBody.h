#pragma once

#include "PhysicsObject.h"

namespace KTEngine::Physics
{
	class CollisionShape;

	class RigidBody final : public PhysicsObject
	{
	public:
		RigidBody() = default;
		~RigidBody() override;

		void Initialize(KTEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f);
		void Terminate();

		void SetPosition(const KTEngine::Math::Vector3& position);
		void SetVelocity(const KTEngine::Math::Vector3& velocity);

		bool isDynamic() const;

	private:
		void SyncGraphics() override;
		btRigidBody* GetRigidBody() override { return mRigidBody; }

		btRigidBody* mRigidBody = nullptr;
		btDefaultMotionState* mMotionState = nullptr;
		float mMass = 0.0f;

		KTEngine::Graphics::Transform* mGraphicsTransform = nullptr;
	};
}