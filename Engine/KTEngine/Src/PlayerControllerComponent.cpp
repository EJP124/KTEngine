#include "Precompiled.h"
#include "PlayerControllerComponent.h"

#include "GameWorld.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "CarModifyComponent.h"
#include "UIButtonComponent.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Input;


void PlayerControllerComponent::Initialize()
{
	mPlayerRb = GetOwner().GetComponent<RigidBodyComponent>();
	mTransformComponent = GetOwner().GetComponent<TransformComponent>();
	mCarModifyComponent = GetOwner().GetComponent<CarModifyComponent>();
}

void PlayerControllerComponent::Terminate()
{
	mCarModifyComponent = nullptr;
	mTransformComponent = nullptr;
	mPlayerRb = nullptr;
	mButtonComponent = nullptr;
	pannel = nullptr;
}

void PlayerControllerComponent::Update(float deltaTime)
{
	auto input = InputSystem::Get();
	if (mPlayerRb != nullptr)
	{
		if (input->IsKeyDown(KeyCode::W))
		{	
			force = (mCarModifyComponent->GetHorsePower() + mCarModifyComponent->GetTireFriction()) * deltaTime ;
		}
		else if (input->IsKeyDown(KeyCode::S))
		{
			if (force <= 0)
			{
				force = 0;
			}
			else
			{
				force -= (mCarModifyComponent->GetTireFriction() + mCarModifyComponent->GetBrakeForce()) * deltaTime;
			}

		}
		else
		{
			if (force <= 0)
			{
				force = 0;
			}
			else
			{
				force -= mCarModifyComponent->GetTireFriction() * deltaTime;
			}
		}

		if (mPlayerRb->GetVelocity() > 0.01)
		{
			if (input->IsKeyDown(KeyCode::A))
			{
				turnAngle = { 0, -0.5, 0 };
			}
			else if (input->IsKeyDown(KeyCode::D))
			{
				turnAngle = { 0, 0.5, 0 };
			}
			else
			{
				turnAngle = Vector3::Zero;
			}
		}
		else
		{
			turnAngle = Vector3::Zero;
		}

		mPlayerRb->SetAngularVelocity(turnAngle);
		Matrix4 matWorld = mTransformComponent->GetMatrix4();
		mPlayerRb->AddForce(Math::GetLook(matWorld) * force, mTransformComponent->position);
	}
	
	if (input->IsKeyPressed(KeyCode::SPACE))
	{
		if (!IsPannelOpen)
		{
			std::filesystem::path templatePath = "../../Assets/Templates/UI/test_screen.json";
			pannel = GetOwner().GetWorld().CreateGameObject("Pannel", templatePath, true);

			for (int i = 0; i < pannel->GetChildSize(); ++i)
			{
				UIButtonComponent* button = pannel->GetChild(i)->GetComponent<UIButtonComponent>();
				switch (i)
				{
				case 0: button->SetCallback([&] {mCarModifyComponent->SetTireType(TireType::Soft); });
					break;
				case 1: button->SetCallback([&] {mCarModifyComponent->SetTireType(TireType::Medium); });
					break;
				case 2: button->SetCallback([&] {mCarModifyComponent->SetTireType(TireType::Hard); });
					break;
				case 3:	button->SetCallback([&] {mCarModifyComponent->SetBrakeSystem(BrakeSystem::Stock); });
					break;
				case 4:	button->SetCallback([&] {mCarModifyComponent->SetBrakeSystem(BrakeSystem::Sport); });
					break;
				case 5: button->SetCallback([&] {mCarModifyComponent->SetBrakeSystem(BrakeSystem::Race); });
					break;
				case 6: button->SetCallback([&] {mCarModifyComponent->SetEngineType(EngineType::V6); });
					break;
				case 7: button->SetCallback([&] {mCarModifyComponent->SetEngineType(EngineType::V8); });
					break;
				case 8: button->SetCallback([&] {mCarModifyComponent->SetEngineType(EngineType::V10); });
					break;
				case 9: button->SetCallback([&] {GetOwner().Save(); });
					break;
				default:
					break;
				}
			}
			IsPannelOpen = true;
		}
		else
		{
			pannel->GetWorld().DestroyGameObject(pannel->GetHandle());
			pannel = nullptr;
			IsPannelOpen = false;
		}
		
	}

	if (pannel != nullptr)
	{
		if (mCarModifyComponent->GetTireFriction() == 60.0f)
		{
			pannel->GetChild(0)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
			pannel->GetChild(1)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(2)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);

		}
		else if (mCarModifyComponent->GetTireFriction() == 30.0f)
		{
			pannel->GetChild(0)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(1)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
			pannel->GetChild(2)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
		}
		else 
		{
			pannel->GetChild(0)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(1)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(2)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
		}
		if (mCarModifyComponent->GetBrakeForce() == 1000.0f)
		{
			pannel->GetChild(3)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
			pannel->GetChild(4)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(5)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
		}
		else if (mCarModifyComponent->GetBrakeForce() == 1200.0f)
		{
			pannel->GetChild(3)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(4)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
			pannel->GetChild(5)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
		}
		else
		{
			pannel->GetChild(3)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(4)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(5)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
		}
		if (mCarModifyComponent->GetHorsePower() == 100.0f)
		{
			pannel->GetChild(6)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
			pannel->GetChild(7)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(8)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
		}
		else if (mCarModifyComponent->GetHorsePower() == 200.0f)
		{
			pannel->GetChild(6)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(7)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
			pannel->GetChild(8)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
		}
		else
		{
			pannel->GetChild(6)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(7)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Default);
			pannel->GetChild(8)->GetComponent<UIButtonComponent>()->SetCurrentState(ButtonState::Click);
		}
	}
}

void PlayerControllerComponent::Serialize(rapidjson::Document& doc, rapidjson::Value& value)
{
	rapidjson::Value componentValue(rapidjson::kObjectType);
	value.AddMember("PlayerControllerComponent", componentValue, doc.GetAllocator());
}






