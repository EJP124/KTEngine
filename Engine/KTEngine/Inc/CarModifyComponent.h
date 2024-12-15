#pragma once

#include "Component.h"

namespace KTEngine
{
	enum class TireType
	{
		Soft,
		Medium,
		Hard
	};

	enum class BrakeSystem
	{
		Stock,
		Sport,
		Race
	};

	enum class EngineType
	{
		V6,
		V8,
		V10
	};
	class CarModifyComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentId::CarModifyComponent);

		void DebugUI() override;
		void Serialize(rapidjson::Document& doc, rapidjson::Value& value)override;
		void Deserialize(const rapidjson::Value& value) override;


		void SetTireType(TireType tire) { t = tire; }
		float GetBrakeForce() { return brakeForce; }
		float GetTireFriction() { return tireFriction; }

	private:
		float brakeForce = 0.0f;
		float tireFriction = 0.0f;
		
		TireType t = TireType::Medium;
		BrakeSystem bs = BrakeSystem::Stock;
		EngineType et = EngineType::V6;
		
	};
}