#pragma once

#include <KTEngine/Inc/KTEngine.h>
using namespace KTEngine;
using namespace KTEngine::Graphics;

class Space
{
public :
	Space(std::string path, float radius);
	void Terminate();
	void Update(float deltaTime);
	void Render(Camera &mCamera, ConstantBuffer &mConstantBuffer);
protected:
	Texture mTexture;
	MeshPC mMesh;
	MeshBuffer mMeshBuffer;

	std::string mTexturePath;

	float _distance;
};