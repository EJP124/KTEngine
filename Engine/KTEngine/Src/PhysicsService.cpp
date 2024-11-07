#include "Precompiled.h"
#include "PhysicsService.h"

#include "SaveUtil.h"

#include "RigidBodyComponent.h"

using namespace KTEngine;
using namespace KTEngine::Physics;

void KTEngine::PhysicsService::Update(float deltaTime)
{
	if (mEnabled)
	{
		PhysicsWorld::Get()->Update(deltaTime);
	}
}

void KTEngine::PhysicsService::DebugUI()
{
	if (mEnabled)
	{
		PhysicsWorld::Get()->DebugUI();
	}
}

void KTEngine::PhysicsService::Serialize(rapidjson::Document& doc, rapidjson::Value& value)
{
	PhysicsWorld::Settings settings = PhysicsWorld::Get()->GetSettings();
	rapidjson::Value serviceValue(rapidjson::kObjectType);
	SaveUtil::SaveVector3("Gravity", settings.gravity, doc, serviceValue);
	SaveUtil::SaveFloat("SimSteps", settings.simulationSteps, doc, serviceValue);
	SaveUtil::SaveFloat("FixedTimeStep", settings.fixedTimeStep, doc, serviceValue);
	value.AddMember("PhysicsService", serviceValue, doc.GetAllocator());
}

void KTEngine::PhysicsService::Deserialize(const rapidjson::Value& value)
{
	PhysicsWorld::Settings settings = PhysicsWorld::Get()->GetSettings();
	if (value.HasMember("Gravity"))
	{
		const auto& gravity = value["Gravity"].GetArray();
		settings.gravity.x = gravity[0].GetFloat();
		settings.gravity.y = gravity[1].GetFloat();
		settings.gravity.z = gravity[2].GetFloat();
	}
	if (value.HasMember("SimSteps"))
	{
		settings.simulationSteps = value["SimSteps"].GetFloat();
	}
	if (value.HasMember("FixedTimeStep"))
	{
		settings.fixedTimeStep = value["FixedTimeStep"].GetFloat();
	}
	PhysicsWorld::Get()->UpdateSettings(settings);
}

void KTEngine::PhysicsService::Register(RigidBodyComponent* rigidBodyComponent)
{
	PhysicsWorld::Get()->Register(&rigidBodyComponent->mRigidBody);
}

void KTEngine::PhysicsService::Unregister(RigidBodyComponent* rigidBodyComponent)
{
	PhysicsWorld::Get()->Unregister(&rigidBodyComponent->mRigidBody);
}

void KTEngine::PhysicsService::SetEnabled(bool enabled)
{
	mEnabled = enabled;
}
