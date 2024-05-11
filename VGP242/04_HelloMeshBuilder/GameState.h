#pragma once
#include <KTEngine/Inc/KTEngine.h>

using namespace KTEngine;
using namespace KTEngine::Graphics;

class GameState : public KTEngine::AppState
{
public:
	virtual ~GameState() = default;

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();
	virtual std::string TexturePath() { return ""; };

	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexShader;
	PixelShader mPixelShader;

	MeshPX mMesh;

	Texture mTexture;
	Sampler mSampler;
};

class SkyBox : public GameState
{
protected:
	void CreateShape() override { mMesh = MeshBuilder::CreateSkyBoxPX(60); };
	std::string TexturePath() override { return "../../Assets/Textures/skybox/skybox_texture.jpg"; };
};

class SkySphere : public GameState
{
protected:
	void CreateShape() override { mMesh = MeshBuilder::CreateSkySpherePX(2, 7, 100);};
	std::string TexturePath() override { return "../../Assets/Textures/skybox/skybox_texture.jpg"; };
};


class GameStatePC : public KTEngine::AppState
{
public:
	virtual ~GameStatePC() = default;

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();

protected:
	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexShader;
	PixelShader mPixelShader;

	MeshPC mMesh;

};

class GroundPlane : public GameStatePC
{
public:
	void CreateShape() override { mMesh = MeshBuilder::CreatePlanePC(1, 1, 100); };
};

class Cube : public GameStatePC
{
public:
	void CreateShape() override { mMesh = MeshBuilder::CreateCubePC(5); };
};

class PyramidPC : public GameStatePC
{
public:
	void CreateShape() override { mMesh = MeshBuilder::CreatePyramidPC(5); };
};

class SpherePC : public GameStatePC
{
public:
	void CreateShape() override { mMesh = MeshBuilder::CreateSpherePC(10,10,100); };
};

class CylinderPC : public GameStatePC
{
public:
	void CreateShape() override { mMesh = MeshBuilder::CreateCylinderPC(5, 5); };
};

