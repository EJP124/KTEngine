#pragma once
#include <KTEngine/Inc/KTEngine.h>

using namespace KTEngine;
using namespace KTEngine::Graphics;

class GameState : public KTEngine::AppState
{
public:
	enum class ShapeType
	{
		Transform,
		Sphere,
		AABB,
		AABBFilled,
		Custom,
		Count
	};
	virtual ~GameState() = default;

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	
	KTEngine::Graphics::Camera mCamera;
	KTEngine::Graphics::MeshPX mMesh;

	KTEngine::Graphics::RenderObject mRenderObject;
	KTEngine::Graphics::StandardEffect mStandardEffect;


};