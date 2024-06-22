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
	KTEngine::Graphics::Reflection mReflectionEffect;

	KTEngine::Graphics::RenderGroup mCharacter;
	KTEngine::Graphics::RenderObject mGround;
	KTEngine::Graphics::RenderObject mBall;

private:
	Vector3 positionSet = { 0,0,0 };
	Vector3 positionSetBall = { 0,0,0 };
	float fov;
};