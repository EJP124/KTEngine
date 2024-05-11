#include "Planet.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

Planet::Planet(std::string path, float radius, float distance)
{
	_distance = distance;
	mMesh = MeshBuilder::CreateSpherePX(20, 20, radius);
	mMeshBuffer.Initialize(mMesh);

	mTexture.Initialize(path);

	mDirection = { 0.0f, 0.0f, 1.0f };
	wDirection = { 0.0f, 0.0f, 1.0f };
	mPosition = { 0.0f, 0.0f, distance };
}

void Planet::Terminate()
{
	mTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Planet::Update(float deltaTime, float rotSpeed, float worldRotSpeed)
{
	Matrix4 matRot = Matrix4::RotationY(1.0f * deltaTime * rotSpeed);
	mDirection = TransformNormal(mDirection, matRot);

	Matrix4 worldRot = Matrix4::RotationY(1.0f * deltaTime * worldRotSpeed);
	wDirection = TransformNormal(wDirection, worldRot);
}

void Planet::Render(Camera& mCamera, ConstantBuffer& mConstantBuffer)
{
	mTexture.BindPS(0);
	Matrix4 matWorld = WorldRot();
	Matrix4 local = Transform();

	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * local * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}

Matrix4 Planet::Transform()
{
	const Math::Vector3 l = mDirection;
	const Math::Vector3 r = Math::Normalize(Math::Cross(Math::Vector3::YAxis, l));
	const Math::Vector3 u = Math::Normalize(Math::Cross(l, r));
	const float x = -Math::Dot(r, mPosition);
	const float y = -Math::Dot(u, mPosition);
	const float z = -Math::Dot(l, mPosition);

	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}


Matrix4 Planet::WorldRot()
{
	Vector3 position = { 0.0f, 0.0f, 0.0f };

	const Math::Vector3 l = wDirection;
	const Math::Vector3 r = Math::Normalize(Math::Cross(Math::Vector3::YAxis, l));
	const Math::Vector3 u = Math::Normalize(Math::Cross(l, r));
	const float x = -Math::Dot(r, position);
	const float y = -Math::Dot(u, position);
	const float z = -Math::Dot(l, position);

	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}



