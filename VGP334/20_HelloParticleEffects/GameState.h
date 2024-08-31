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
	KTEngine::Graphics::ParticleSystemEffect mParticleEffect;
	KTEngine::Physics::ParticleSystem mParticleSystem;
};