#pragma once
#include <KTEngine/Inc/KTEngine.h>
#include "Planet.h"

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
	void DebugUI() override;
protected:
	virtual void CreateShape();
private:
	void UpdateCameraControl(float deltaTime);
	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	VertexShader mVertexShader;
	PixelShader mPixelShader;
	Sampler mSampler;

	bool _drawCir;
	bool _drawPlane;
	Color _debugColor;

	std::vector<float> worldRotSpeed =
	{
		0, //sun
		1, //mercury
		1, //venus
		1, //earth
		1, //mars
		1, //jupiter
		1, //saturn
		1,  //uranus
		1  //pluto
	};

	std::vector<float> selfRotSpeed =
	{
		0, //sun
		1, //mercury
		1, //venus
		1, //earth
		1, //mars
		1, //jupiter
		1, //saturn
		1,  //uranus
		1  //pluto
	};

	std::vector<std::shared_ptr<Planet>> mPlanets;
	MeshPX mMesh;
	MeshBuffer mMeshBuffer;
	Texture mTexture;
};