#include "Space.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

Space::Space(std::string path, float radius)
{
	mMesh = MeshBuilder::CreateSpherePC(100, 100, radius);
	mMeshBuffer.Initialize(mMesh);

	mTexture.Initialize(path);

	
}

void Space::Terminate()
{
	mTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Space::Update(float deltaTime)
{
	
}
float totalTime = 0.0f;
float yRot = 0.0f;
float xRot = 0.0f;
Vector3 position(0.0f);
void Space::Render(Camera& mCamera, ConstantBuffer& mConstantBuffer)
{
	mTexture.BindPS(0);

	Matrix4 matWorld = Matrix4::RotationX(xRot) * Matrix4::RotationY(yRot) * Matrix4::Translation(position);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}








