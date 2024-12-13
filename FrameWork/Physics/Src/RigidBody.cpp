#include "Precompiled.h"
#include "RigidBody.h"
#include "CollisionShape.h"
#include "PhysicsWorld.h"

using namespace KTEngine;
using namespace KTEngine::Physics;
using namespace KTEngine::Math;
using namespace KTEngine::Graphics;

RigidBody::~RigidBody()
{
	ASSERT(mRigidBody == nullptr && mMotionState == nullptr, "RigidBody: terminate must be called");
}

void RigidBody::Initialize(KTEngine::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
	mGraphicsTransform = &graphicsTransform;
	mMass = mass;

	mMotionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
	mRigidBody = new btRigidBody(mass, mMotionState, shape.GetCollisionShape());

#ifndef USE_PHYSICS_SERVICE
	PhysicsWorld::Get()->Register(this);
#endif
}

void RigidBody::Terminate()
{
#ifndef USE_PHYSICS_SERVICE
	PhysicsWorld::Get()->Unregister(this);
#endif
	SafeDelete(mRigidBody);
	SafeDelete(mMotionState);
	mGraphicsTransform = nullptr;
}

void RigidBody::SetPosition(const KTEngine::Math::Vector3& position)
{
	if (isDynamic())
	{
		mRigidBody->activate();
	}
	mGraphicsTransform->position = position;
	mRigidBody->setWorldTransform(ConvertTobtTransform(*mGraphicsTransform));
}

void RigidBody::SetVelocity(const KTEngine::Math::Vector3& velocity)
{
	mRigidBody->activate();
	mRigidBody->setLinearVelocity(ConvertTobtVector3(velocity));
}

void RigidBody::AddForce(const KTEngine::Math::Vector3& force, const KTEngine::Math::Vector3& position)
{
	mRigidBody->activate();
	mRigidBody->applyForce(ConvertTobtVector3(force), ConvertTobtVector3(position));
;}

void RigidBody::SetAngularVelocity(const KTEngine::Math::Vector3& angularVelocity)
{
	mRigidBody->activate();
	mRigidBody->setAngularVelocity(ConvertTobtVector3(angularVelocity));
}

Vector3 RigidBody::GetVelocity()
{
	mRigidBody->activate();
	return ConvertToVector3(mRigidBody->getLinearVelocity());
}

bool RigidBody::isDynamic() const
{
	return mMass > 0.0f;
}

void RigidBody::SyncGraphics()
{
	ApplybtTransform(*mGraphicsTransform, mRigidBody->getWorldTransform());
}
