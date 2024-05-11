#include "GameState.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Math;
using namespace KTEngine::Input;

namespace
{
	void ChangeState()
	{
		auto input = Input::InputSystem::Get();
		if (input->IsKeyDown(KeyCode::ONE))
		{
			MainApp().ChangeState("StateOne");
		}
		if (InputSystem::Get()->IsKeyPressed(KeyCode::TWO))
		{
			MainApp().ChangeState("StateTWO");
		}
		if (InputSystem::Get()->IsKeyPressed(KeyCode::THREE))
		{
			MainApp().ChangeState("StateTHREE");
		}
		if (InputSystem::Get()->IsKeyPressed(KeyCode::FOUR))
		{
			MainApp().ChangeState("StateFOUR");
		}
		if (InputSystem::Get()->IsKeyPressed(KeyCode::FIVE))
		{
			MainApp().ChangeState("StateFIVE");
		}
		if (InputSystem::Get()->IsKeyPressed(KeyCode::SIX))
		{
			MainApp().ChangeState("StateSIX");
		}
		if (InputSystem::Get()->IsKeyPressed(KeyCode::SEVEN))
		{
			MainApp().ChangeState("StateSEVEN");
		}
	}
}

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	// create shapes in NDC normalized device coordinate
	// -1 to 1 (x, y, z)
	CreateShape();
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexturing.fx";

	mConstantBuffer.Initialize(sizeof(Matrix4));
	// Create a vertex buffer
	mMeshBuffer.Initialize(mMesh);

	// Create a vertex shader
	mVertexShader.Initialize<VertexPX>(shaderFile);

	// Create a pixel shader
	mPixelShader.Initialize(shaderFile);

	mTexture.Initialize(TexturePath());
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameState::CreateShape()
{
	mMesh = MeshBuilder::CreateSkyBoxPX(60);
}

void GameState::Terminate()
{
	mSampler.Terminate();
	mTexture.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

float totalTime = 0.0f;
float yRot = 0.0f;
float xRot = 0.0f;
Vector3 position(0.0f);
void GameState::Update(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.8f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::LBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	ChangeState();
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mTexture.BindPS(0);
	mSampler.BindPS(0);

	Matrix4 matWorld = Matrix4::RotationX(xRot) * Matrix4::RotationY(yRot) * Matrix4::Translation(position);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}

void GameStatePC::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	// create shapes in NDC normalized device coordinate
	// -1 to 1 (x, y, z)
	CreateShape();
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";

	mConstantBuffer.Initialize(sizeof(Matrix4));
	// Create a vertex buffer
	mMeshBuffer.Initialize(mMesh);

	// Create a vertex shader
	mVertexShader.Initialize<VertexPX>(shaderFile);
		
	// Create a pixel shader
	mPixelShader.Initialize(shaderFile);

}

void GameStatePC::CreateShape()
{
	mMesh = MeshBuilder::CreateCylinderPC(10, 10);
}

void GameStatePC::Terminate()
{
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void GameStatePC::Update(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.8f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::LBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	ChangeState();
}

void GameStatePC::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	Matrix4 matWorld = Matrix4::RotationX(xRot) * Matrix4::RotationY(yRot) * Matrix4::Translation(position);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}