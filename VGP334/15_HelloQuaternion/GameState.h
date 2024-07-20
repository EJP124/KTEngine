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

	KTEngine::Graphics::RenderGroup mCharacter;
	KTEngine::Graphics::StandardEffect mStandardEffect;

	float mYaw = 0.0f;
	float mPitch = 0.0f;
	float mRoll = 0.0f;

	KTEngine::Graphics::Transform mTransform;
};