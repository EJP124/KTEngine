#include "Precompiled.h"
#include "GeometryShader.h"
#include "GraphicsSystem.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;


void GeometryShader::Initialize(const std::filesystem::path& filePath, uint32_t format)
{
	auto device = GraphicsSystem::Get()->GetDevice();
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

    HRESULT hr = D3DCompileFromFile(
        filePath.c_str(),
        nullptr,
        nullptr,
        "GS",            // Entry point name
        "gs_5_0",        // Target shader model
        D3DCOMPILE_ENABLE_STRICTNESS,
        0,
        &shaderBlob,
        &errorBlob
    );

    if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
    {
        LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
    }
    ASSERT(SUCCEEDED(hr), "Failed to compile geometry shader");

    hr = device->CreateGeometryShader(
        shaderBlob->GetBufferPointer(),
        shaderBlob->GetBufferSize(), 
        nullptr, 
        &mGeometryShader);
    ASSERT(SUCCEEDED(hr), "Failed to create geometry shader");

    SafeRelease(shaderBlob);
    SafeRelease(errorBlob);
}

void GeometryShader::Terminate()
{
    SafeRelease(mGeometryShader);
}

void GeometryShader::Bind()
{
    auto context = GraphicsSystem::Get()->GetContext();
    context->GSSetShader(mGeometryShader, nullptr, 0);
}

