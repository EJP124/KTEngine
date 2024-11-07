#pragma once

// framework headers
#include <Math/Inc/KTMath.h>
#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>

//bullet files
#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include <Bullet/BulletSoftBody/btSoftBodyHelpers.h>
#include <Bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <Bullet/BulletSoftBody/btSoftBodySolvers.h>

#define USE_SOFT_BODY
#define USE_PHYSICS_SERVICE

// helper functions
template<class T>
inline void SafeDelete(T*& ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

//math helper functions
inline btVector3 ConvertTobtVector3(const KTEngine::Math::Vector3& v)
{
	return btVector3(v.x, v.y, v.z);
}
inline btQuaternion ConvertTobtQuaternion(const KTEngine::Math::Quaternion& q)
{
	return btQuaternion(q.x, q.y, q.z);
}
inline btTransform ConvertTobtTransform(const KTEngine::Graphics::Transform& transform)
{
	return btTransform(ConvertTobtQuaternion(transform.rotation), ConvertTobtVector3(transform.position));
}

inline KTEngine::Math::Vector3 ConvertToVector3(const btVector3& v)
{
	return { v.getX(), v.getY(), v.getZ() };
}
inline KTEngine::Math::Quaternion ConvertToQuaternion(const btQuaternion& q)
{
	return { q.getX(), q.getY(), q.getZ(), q.getW() };
}
inline void ApplybtTransform(KTEngine::Graphics::Transform& transform, const btTransform& t)
{
	transform.position = ConvertToVector3(t.getOrigin());
	transform.rotation = ConvertToQuaternion(t.getRotation());
}