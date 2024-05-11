#pragma once

#include <KTEngine/Inc/KTEngine.h>
using namespace KTEngine;
using namespace KTEngine::Graphics;

class Planet
{
public :
	Planet(std::string path, float radius, float distance);
	void Terminate();
	void Update(float deltaTime, float rotSpeed, float worldRot);
	void Render(Camera &mCamera, ConstantBuffer &mConstantBuffer);
	float GetDistance() { return _distance; }

	Matrix4 Transform();
	Matrix4 WorldRot();
protected:
	Texture mTexture;
	MeshPX mMesh;
	MeshBuffer mMeshBuffer;

	Vector3 mPosition;
	Vector3 mDirection;

	Vector3 wDirection;

	std::string mTexturePath;

	float _distance;
};