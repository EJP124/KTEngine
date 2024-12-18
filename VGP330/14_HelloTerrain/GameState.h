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

	KTEngine::Graphics::StandardEffect mStandardEffect;
	KTEngine::Graphics::ShadowEffect mShadowEffect;
	KTEngine::Graphics::TerrainEffect mTerrainEffect;

	KTEngine::Graphics::Terrain mTerrain;
	KTEngine::Graphics::RenderGroup mCharacter;
	KTEngine::Graphics::RenderObject mGround;


	bool mOnTerrain = false;
};