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

	KTEngine::Graphics::RenderObject mGround;
	KTEngine::Graphics::RenderObject mBall;

	KTEngine::Physics::CollisionShape mBallShape;
	KTEngine::Physics::RigidBody mBallRB;

	KTEngine::Physics::CollisionShape mGroundShape;
	KTEngine::Physics::RigidBody mGroundRB;


};