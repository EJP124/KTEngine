#include "Precompiled.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Component.h"
#include "AnimatorComponent.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"
#include "ThirdPersonCameraComponent.h"
#include "PlayerControllerComponent.h"
#include "CarModifyComponent.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "ModelComponent.h"
#include "RigidBodyComponent.h"
#include "SoundBankComponent.h"
#include "SoundEffectComponent.h"
#include "UITextComponent.h"
#include "UISpriteComponent.h"
#include "UIButtonComponent.h"
#include "GameWorld.h"

using namespace KTEngine;

namespace
{
	CustomMake TryMake;
	CustomGet TryGet;

	Component* AddComponent(const std::string& componentName, GameObject& gameObject)
	{
		Component* newComponent = nullptr;
		if (componentName == "TransformComponent")
		{
			newComponent = gameObject.AddComponent<TransformComponent>();
		}
		else if (componentName == "CameraComponent")
		{
			newComponent = gameObject.AddComponent<CameraComponent>();
		}
		else if (componentName == "FPSCameraComponent")
		{
			newComponent = gameObject.AddComponent<FPSCameraComponent>();
		}
		else if (componentName == "ThirdPersonCameraComponent")
		{
			newComponent = gameObject.AddComponent<ThirdPersonCameraComponent>();
		}
		else if (componentName == "PlayerControllerComponent")
		{
			newComponent = gameObject.AddComponent<PlayerControllerComponent>();
		}
		else if (componentName == "CarModifyComponent")
		{
			newComponent = gameObject.AddComponent<CarModifyComponent>();
		}
		else if (componentName == "MeshComponent")
		{
			newComponent = gameObject.AddComponent<MeshComponent>();
		}
		else if (componentName == "AnimatorComponent")
		{
			newComponent = gameObject.AddComponent<AnimatorComponent>();
		}
		else if (componentName == "ModelComponent")
		{
			newComponent = gameObject.AddComponent<ModelComponent>();
		}
		else if (componentName == "RigidBodyComponent")
		{
			newComponent = gameObject.AddComponent<RigidBodyComponent>();
		}
		else if (componentName == "SoundBankComponent")
		{
			newComponent = gameObject.AddComponent<SoundBankComponent>();
		}
		else if (componentName == "SoundEffectComponent")
		{
			newComponent = gameObject.AddComponent<SoundEffectComponent>();
		}
		else if (componentName == "UITextComponent")
		{
			newComponent = gameObject.AddComponent<UITextComponent>();
		}
		else if (componentName == "UISpriteComponent")
		{
			newComponent = gameObject.AddComponent<UISpriteComponent>();
		}
		else if (componentName == "UIButtonComponent")
		{
			newComponent = gameObject.AddComponent<UIButtonComponent>();
		}
		else
		{
			newComponent = TryMake(componentName, gameObject);
			ASSERT(false, "GameObjectFactory: unrecognized component %s", componentName.c_str());
		}

		return newComponent;
	}
	Component* GetComponent(const std::string& componentName, GameObject& gameObject)
	{
		Component* newComponent = nullptr;
		if (componentName == "TransformComponent")
		{
			newComponent = gameObject.GetComponent<TransformComponent>();
		}
		else if (componentName == "CameraComponent")
		{
			newComponent = gameObject.GetComponent<CameraComponent>();
		}
		else if (componentName == "FPSCameraComponent")
		{
			newComponent = gameObject.GetComponent<FPSCameraComponent>();
		}
		else if (componentName == "ThirdPersonCameraComponent")
		{
			newComponent = gameObject.GetComponent<ThirdPersonCameraComponent>();
		}
		else if (componentName == "PlayerControllerComponent")
		{
			newComponent = gameObject.GetComponent<PlayerControllerComponent>();
		}
		else if (componentName == "CarModifyComponent")
		{
			newComponent = gameObject.GetComponent<CarModifyComponent>();
		}
		else if (componentName == "MeshComponent")
		{
			newComponent = gameObject.GetComponent<MeshComponent>();
		}
		else if (componentName == "AnimatorComponent")
		{
			newComponent = gameObject.GetComponent<AnimatorComponent>();
		}
		else if (componentName == "ModelComponent")
		{
			newComponent = gameObject.GetComponent<ModelComponent>();
		}
		else if (componentName == "RigidBodyComponent")
		{
			newComponent = gameObject.GetComponent<RigidBodyComponent>();
		}
		else if (componentName == "SoundBankComponent")
		{
			newComponent = gameObject.GetComponent<SoundBankComponent>();
		}
		else if (componentName == "SoundEffectComponent")
		{
			newComponent = gameObject.GetComponent<SoundEffectComponent>();
		}
		else if (componentName == "UITextComponent")
		{
			newComponent = gameObject.GetComponent<UITextComponent>();
		}
		else if (componentName == "UISpriteComponent")
		{
			newComponent = gameObject.GetComponent<UISpriteComponent>();
		}
		else if (componentName == "UIButtonComponent")
		{
			newComponent = gameObject.GetComponent<UIButtonComponent>();
		}
		else
		{
			newComponent = TryGet(componentName, gameObject);
			ASSERT(false, "GameObjectFactory: unrecognized component %s", componentName.c_str());
		}

		return newComponent;
	}
}

void GameObjectFactory::SetCustomMake(CustomMake customMake)
{
	TryMake = customMake;
}

void GameObjectFactory::SetCustomGet(CustomGet customGet)
{
	TryGet = customGet;
}

void GameObjectFactory::Make(const std::filesystem::path& templatePath, GameObject& gameObject, GameWorld& gameWorld)
{
	FILE* file = nullptr;
	auto err = fopen_s(&file, templatePath.u8string().c_str(), "r");
	ASSERT(err = 0, "GameObjectFactory: failed to open file %s", templatePath.u8string().c_str());

	char readBuffer[65536];
	rapidjson::FileReadStream readStream(file, readBuffer, sizeof(readBuffer));
	fclose(file);

	rapidjson::Document doc;
	doc.ParseStream(readStream);
	auto components = doc["Components"].GetObj();
	for (auto& component : components)
	{
		Component* newComponent = AddComponent(component.name.GetString(), gameObject);
		if (newComponent != nullptr)
		{
			newComponent->Deserialize(component.value);
		}
	}
	if (doc.HasMember("Children"))
	{
		auto children = doc["Children"].GetObj();
		for (auto& child : children)
		{
			std::string name = child.name.GetString();
			std::filesystem::path childTemplate = child.value["Template"].GetString();
			GameObject* go = gameWorld.CreateGameObject(name, childTemplate);
			GameObjectFactory::OverrideDeserialize(child.value, *go);

			gameObject.AddChild(go);
			go->SetParent(&gameObject);
		}

	}
}
void GameObjectFactory::OverrideDeserialize(const rapidjson::Value& value, GameObject& gameObject)
{
	if (value.HasMember("Components"))
	{
		auto components = value["Components"].GetObj();
		for (auto& component : components)
		{
			Component* ownedComponent = GetComponent(component.name.GetString(), gameObject);
			if (ownedComponent != nullptr)
			{
				ownedComponent->Deserialize(component.value);
			}
		}
	}
}