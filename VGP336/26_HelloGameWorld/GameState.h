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

protected:
	KTEngine::GameWorld mGameWorld;
};