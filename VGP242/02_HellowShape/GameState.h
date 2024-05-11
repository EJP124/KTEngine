#pragma once

#include <KTEngine/Inc/KTEngine.h>

class GameState : public KTEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

	
protected:
	virtual void CreateShape() {}
	struct Vertex
	{
		KTEngine::Math::Vector3 position;
		KTEngine::Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
	

};
class Triangle : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};

class Square : public GameState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};



