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
	KTEngine::Graphics::PostProcessingEffect mPostProcessingEffect;

	KTEngine::Graphics::RenderGroup mCharacter;
	KTEngine::Graphics::RenderGroup mCharacter2;
	KTEngine::Graphics::RenderObject mGround;

	KTEngine::Graphics::RenderTarget mRenderTarget;
	KTEngine::Graphics::RenderObject mScreenQuad;
	KTEngine::Graphics::Texture mCombinTexture;
private:
	Vector3 positionSet = { 0,0,0 };
	Vector3 positionSet2 = { 0,0,0 };
};