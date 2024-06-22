#pragma once
#include <KTEngine/Inc/KTEngine.h>

using namespace KTEngine;
using namespace KTEngine::Graphics;

class GameState : public KTEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
	void UpdateCameraControl(float deltaTime);

protected:
	KTEngine::Graphics::DirectionalLight mDirectionalLight;
	KTEngine::Graphics::Camera mCamera;
	KTEngine::Graphics::Camera mCameraTarget;
	KTEngine::Graphics::Camera mCameras[6];

	KTEngine::Graphics::StandardEffect mStandardEffect;
	KTEngine::Graphics::ShadowEffect mShadowEffect;
	KTEngine::Graphics::TerrainEffect mTerrainEffect;
	KTEngine::Graphics::Reflection mReflectionEffect;

	KTEngine::Graphics::Terrain mTerrain;
	KTEngine::Graphics::RenderGroup mCharacter;
	KTEngine::Graphics::RenderObject mGround;
	KTEngine::Graphics::RenderTarget mTargers[6];

	Texture mTexture;

	Vector3 positionSet = { 0,0,0 };


	bool mOnTerrain = false;
};