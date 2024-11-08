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
	void OnEvent2();
	void OnEvent3();

	void OnSpaceEvent(const KTEngine::Event* event);
	void OnAnimEvent(const KTEngine::Event* event);

	KTEngine::Graphics::DirectionalLight mDirectionalLight;
	KTEngine::Graphics::Camera mCamera;

	KTEngine::Graphics::ModelId mModelId;
	KTEngine::Graphics::RenderGroup mCharacter;
	KTEngine::Graphics::Animator mCharacterAnimator;
	KTEngine::Graphics::StandardEffect mStandardEffect;

	KTEngine::ListenerId mSpaceEventId = 0;
	KTEngine::ListenerId mAnimEventId = 0;

	std::vector<KTEngine::Audio::SoundId> mSoundEventIds;
	KTEngine::Graphics::Animation mEventAnimation;
	float mEventAnimationTime = 0.0f;

	int mAnimIndex = -1;
	bool mDrawSkeleton = false;
};