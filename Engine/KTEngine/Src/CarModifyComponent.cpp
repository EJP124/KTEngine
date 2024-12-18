#include "Precompiled.h"
#include "CarModifyComponent.h"

#include "SaveUtil.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;


void CarModifyComponent::DebugUI()
{
	if (ImGui::CollapsingHeader("CarComponent", ImGuiTreeNodeFlags_DefaultOpen))
	{

		bool useSoftTire = t == TireType::Soft;
		if (ImGui::Checkbox("SoftTire", &useSoftTire))
		{
			t = TireType::Soft;
		}
		ImGui::SameLine(0, 20);
		bool useMediumTire = t == TireType::Medium;
		if (ImGui::Checkbox("MediumTire", &useMediumTire))
		{
			t = TireType::Medium;
		}
		ImGui::SameLine(0, 20);
		bool useHardTire = t == TireType::Hard;
		if (ImGui::Checkbox("HardTire", &useHardTire))
		{
			t = TireType::Hard;
		}

		bool useStockBrake = bs == BrakeSystem::Stock;
		if (ImGui::Checkbox("StockBrake", &useStockBrake))
		{
			bs = BrakeSystem::Stock;
		}
		ImGui::SameLine(0, 20);
		bool useSportBrake = bs == BrakeSystem::Sport;
		if (ImGui::Checkbox("SportBrake", &useSportBrake))
		{
			bs = BrakeSystem::Sport;
		}
		ImGui::SameLine(0, 20);
		bool useRaceBrake = bs == BrakeSystem::Race;
		if (ImGui::Checkbox("RaceBrake", &useRaceBrake))
		{
			bs = BrakeSystem::Race;
		}

		bool useV6Engine = et == EngineType::V6;
		if (ImGui::Checkbox("V6", &useV6Engine))
		{
			et = EngineType::V6;
		}
		ImGui::SameLine(0, 20);
		bool useV8Engine = et == EngineType::V8;
		if (ImGui::Checkbox("V8", &useV8Engine))
		{
			et = EngineType::V8;
		}
		ImGui::SameLine(0, 20);
		bool useV10Engine = et == EngineType::V10;
		if (ImGui::Checkbox("V10", &useV10Engine))
		{
			et = EngineType::V10;
		}
	}
}

void CarModifyComponent::Serialize(rapidjson::Document& doc, rapidjson::Value& value)
{
	rapidjson::Value componentValue(rapidjson::kObjectType);
	SaveUtil::SaveInt("Tire", static_cast<int>(t), doc,componentValue);
	SaveUtil::SaveInt("Brake", static_cast<int>(bs), doc,componentValue);
	SaveUtil::SaveInt("Enigne", static_cast<int>(et), doc,componentValue);
	value.AddMember("CarModifyComponent", componentValue, doc.GetAllocator());
}

void CarModifyComponent::Deserialize(const rapidjson::Value& value)
{
	if (value.HasMember("Tire"))
	{
		int tireType = value["Tire"].GetInt();
		if (tireType == 0)
		{
			t = TireType::Soft;
		}
		else if (tireType == 1)
		{
			t = TireType::Medium;
		}
		else if (tireType == 2)
		{
			t = TireType::Hard;
		}
	}
	if (value.HasMember("Brake"))
	{
		int brakeType  = value["Brake"].GetInt();
		if (brakeType == 0)
		{
			bs = BrakeSystem::Stock;
		}
		else if (brakeType == 1)
		{
			bs = BrakeSystem::Sport;
		}
		else if (brakeType == 2)
		{
			bs = BrakeSystem::Race;
		}
	}
	if (value.HasMember("Engine"))
	{
		int engineType = value["Engine"].GetInt();
		if (engineType == 0)
		{
			et = EngineType::V6;
		}
		else if (engineType == 1)
		{
			et = EngineType::V8;
		}
		else if (engineType == 2)
		{
			et = EngineType::V10;
		}
	}
}

float CarModifyComponent::GetBrakeForce()
{
	if (bs == BrakeSystem::Stock)
	{
		return 1000.0f;
	}
	else if (bs == BrakeSystem::Sport)
	{
		return 1200.0f;
	}
	else if (bs == BrakeSystem::Race)
	{
		return 2500.0f;
	}
}

float CarModifyComponent::GetTireFriction()
{
	if (t == TireType::Soft)
	{
		return 60.0f;
	}
	else if (t == TireType::Medium)
	{
		return 30.0f;
	}
	else if (t == TireType::Hard)
	{
		return 10.0f;
	}
}

float KTEngine::CarModifyComponent::GetHorsePower()
{
	if (et == EngineType::V6)
	{
		return 100.0f;
	}
	else if (et == EngineType::V8)
	{
		return 200.0f;
	}
	else if (et == EngineType::V10)
	{
		return 300.0f;
	}
}
