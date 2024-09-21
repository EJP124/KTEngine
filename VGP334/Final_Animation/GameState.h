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

	void BallAnimation();
	void Animation1();
	void Animation2();
	void OnEvent();
	void ParticleEffect();

protected:
	KTEngine::Graphics::DirectionalLight mDirectionalLight;
	KTEngine::Graphics::Camera mCamera;
	KTEngine::Graphics::StandardEffect mStandardEffect;

	KTEngine::Graphics::RenderObject mGround;
	KTEngine::Graphics::RenderObject mBall;


	KTEngine::Graphics::ModelId mModelId;
	KTEngine::Graphics::RenderGroup mCharacter;
	KTEngine::Graphics::Animator mCharacterAnimator;

	KTEngine::Graphics::ModelId mModelId1;
	KTEngine::Graphics::RenderGroup mCharacter1;
	KTEngine::Graphics::Animator mCharacterAnimator1;

	KTEngine::Graphics::Animation mAnimation;
	KTEngine::Graphics::Animation mAnimation1;
	KTEngine::Graphics::Animation mAnimation2;

	std::vector<KTEngine::Audio::SoundId> mSoundEventIds;

	KTEngine::Graphics::ParticleSystemEffect mParticleEffect;
	KTEngine::Physics::ParticleSystem mParticleSystem;
	float mAnimationTime;
	int mAnimIndex = -1;
	bool mDrawSkeleton = false;
};