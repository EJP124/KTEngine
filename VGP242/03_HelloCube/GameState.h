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
	KTEngine::Graphics::MeshPC mMesh;
	KTEngine::Graphics::MeshBuffer mMeshBuffer;

	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;


};