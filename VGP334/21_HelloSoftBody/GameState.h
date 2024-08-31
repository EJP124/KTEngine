#pragma once

#include <KTEngine/Inc/KTEngine.h>

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

	KTEngine::Graphics::RenderObject mBall;
	KTEngine::Physics::CollisionShape mBallShape;
	KTEngine::Physics::RigidBody mBallRB;

	KTEngine::Graphics::RenderObject mGround;
	KTEngine::Physics::CollisionShape mGroundShape;
	KTEngine::Physics::RigidBody mGroundRB;

	KTEngine::Graphics::RenderObject mCloth;
	KTEngine::Graphics::Mesh mClothMesh;
	KTEngine::Physics::SoftBody mClothSoftBody;
};