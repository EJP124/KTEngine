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

		
		void SetTireType(TireType tyre)
		{
			t = tyre;
		}
		void SetBrakeSystem(BrakeSystem brake) { bs = brake; }
		void SetEngineType(EngineType engine) { et = engine; }
		float GetBrakeForce();
		float GetTireFriction();
		float GetHorsePower();

	private:
		TireType t = TireType::Medium;
		BrakeSystem bs = BrakeSystem::Stock;
		EngineType et = EngineType::V6;
		
	};
}