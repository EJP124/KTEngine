#pragma once

#include "CustomTypeIds.h"

class CustomDebugDrawComponent : public KTEngine::Component
{
public:
	SET_TYPE_ID(CustomCompoenntId::CustomDebugDraw);

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Deserialize(const rapidjson::Value& value) override;

	void AddDebugDraw();

private:
	const KTEngine::TransformComponent* mTransformComponent = nullptr;
	KTEngine::Math::Vector3 mPosition = KTEngine::Math::Vector3::Zero;
	KTEngine::Color mColor = KTEngine::Colors::White;
	uint32_t mSlices = 0;
	uint32_t mRings = 0;
	float mRadius = 0.0f;
};