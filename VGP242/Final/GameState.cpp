#include "GameState.h"


using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Math;
using namespace KTEngine::Input;
using namespace KTEngine::Colors;



void GameState::Initialize()
{
	_drawCir = true;
	_drawPlane = true;
	_debugColor = Colors::White;
	mCamera.SetPosition({ 100.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";

	mConstantBuffer.Initialize(sizeof(Matrix4));

	// Create a vertex shader
	mVertexShader.Initialize<VertexPX>(shaderFile);

	// Create a pixel shader
	mPixelShader.Initialize(shaderFile);

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mMesh = MeshBuilder::CreateSkySpherePX(100, 100, 1000);
	mMeshBuffer.Initialize(mMesh);
	mTexture.Initialize("../../Assets/Textures/skysphere/space.jpg");
	CreateShape();
}

void GameState::CreateShape() 
{ 
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/sun.jpg", 10.0f, 0.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/mercury.jpg", 0.8f, 20.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/venus.jpg", 3.0f, 30.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/earth/earth.jpg", 3.0f, 40.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/mars.jpg", 1.0f, 80.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/jupiter.jpg", 5.0f, 100.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/saturn.jpg", 4.0f, 120.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/uranus.jpg", 1.0f, 140.0f));
	mPlanets.push_back(std::make_shared<Planet>("../../Assets/Textures/planets/pluto.jpg", 1.0f, 240.0f));

	
}



void GameState::Terminate()
{
	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	
	for (int i = 0; i < mPlanets.size(); i++)
	{
		mPlanets[i]->Terminate();
	}
	//mSpace.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCameraControl(deltaTime);
	for (int i = 0; i < mPlanets.size(); i++)
	{
		mPlanets[i]->Update(deltaTime, worldRotSpeed[i], selfRotSpeed[i]);
	}
	//mSpace.Update(deltaTime);
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mSampler.BindPS(0);
	mTexture.BindPS(0);
	//mSpace.Render(mCamera, mConstantBuffer);
	mMeshBuffer.Render();

	for (int i = 0; i < mPlanets.size(); i++)
	{
		mPlanets[i]->Render(mCamera, mConstantBuffer);
		if (_drawCir)
		{
			SimpleDraw::AddGroundCircle(1000, mPlanets[i]->GetDistance(), _debugColor);
		}
	}

	SimpleDraw::Render(mCamera);
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug UI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Draw Route", &_drawCir);
	
	ImGui::DragFloat("Sun worldRotSpeed##", &worldRotSpeed[0], 0.2f, -20.0f);
	ImGui::DragFloat("mercury worldRotSpeed##", &worldRotSpeed[1], 0.2f, -20.0f);
	ImGui::DragFloat("venus worldRotSpeed##", &worldRotSpeed[2], 0.2f, -20.0f);
	ImGui::DragFloat("earth worldRotSpeed##", &worldRotSpeed[3], 0.2f, -20.0f);
	ImGui::DragFloat("mars worldRotSpeed##", &worldRotSpeed[4], 0.2f, -20.0f);
	ImGui::DragFloat("jupiter worldRotSpeed##", &worldRotSpeed[5], 0.2f, -20.0f);
	ImGui::DragFloat("saturn worldRotSpeed##", &worldRotSpeed[6], 0.2f, -20.0f);
	ImGui::DragFloat("uranus worldRotSpeed##", &worldRotSpeed[7], 0.2f, -20.0f);
	ImGui::DragFloat("pluto worldRotSpeed##", &worldRotSpeed[8], 0.2f, -20.0f);

	ImGui::DragFloat("Sun selfRotSpeed##", &selfRotSpeed[0], 0.2f, -20.0f);
	ImGui::DragFloat("mercury selfRotSpeed##", &selfRotSpeed[1], 0.2f, -20.0f);
	ImGui::DragFloat("venus selfRotSpeed##", &selfRotSpeed[2], 0.2f, -20.0f);
	ImGui::DragFloat("earth selfRotSpeed##", &selfRotSpeed[3], 0.2f, -20.0f);
	ImGui::DragFloat("mars selfRotSpeed##", &selfRotSpeed[4], 0.2f, -20.0f);
	ImGui::DragFloat("jupiter selfRotSpeed##", &selfRotSpeed[5], 0.2f, -20.0f);
	ImGui::DragFloat("saturn selfRotSpeed##", &selfRotSpeed[6], 0.2f, -20.0f);
	ImGui::DragFloat("uranus selfRotSpeed##", &selfRotSpeed[7], 0.2f, -20.0f);
	ImGui::DragFloat("pluto selfRotSpeed##", &selfRotSpeed[8], 0.2f, -20.0f);
	
	ImGui::ColorEdit4("RouteCOlor##", &_debugColor.r);
	ImGui::End();
}

void GameState::UpdateCameraControl(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}
