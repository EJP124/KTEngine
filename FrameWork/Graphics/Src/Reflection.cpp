#include "Precompiled.h"
#include "Reflection.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "GraphicsSystem.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

void Reflection::Initialize()
{
    std::filesystem::path shaderFile = "../../Assets/Shaders/Reflection.fx";
    mTransformBuffer.Initialize();
    mReflectionBuffer.Initialize();
    mVertexShader.Initialize<Vertex>(shaderFile);
    mPixelShader.Initialize(shaderFile);
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
    GraphicsSystem* gs = GraphicsSystem::Get();
    const uint32_t screenWidth = gs->GetBackBufferWidth();
    const uint32_t screenHeight = gs->GetBackBufferHeight();
    /*for (int i = 0; i < 6; ++i)
    {
        mTargets[i].Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
    }*/
    //mSkybox.Initialize("../../Assets/Textures/skybox/skybox_texture.jpg");
    mTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
}

void Reflection::Terminate()
{
    mSampler.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mTransformBuffer.Terminate();
    mReflectionBuffer.Terminate();
    /*for (int i = 0; i < 6; ++i)
    {
        mTargets[i].Terminate();
    }*/
    mTarget.Terminate();
}

void Reflection::Begin()
{
    ASSERT(mCamera != nullptr, "ReflectionEffect: no camera set!");
    mVertexShader.Bind();
    mPixelShader.Bind();

    mSampler.BindVS(0);
    mSampler.BindPS(0);

    mTransformBuffer.BindVS(0);
    mTransformBuffer.BindPS(0);
    mReflectionBuffer.BindVS(1);

    /*for (int i = 0; i < 6; ++i)
    {
        mTargets[i].BindPS(1);
    }*/
    mTarget.BindPS(0);


    if (mReflectionMap != nullptr)
    {
        mReflectionMap->BindPS(0);
    }
}

void Reflection::End()
{
    if (mReflectionMap != nullptr)
    {
        Texture::UnbindPS(0); 
    }
    
}

void Reflection::Render(const RenderObject& renderObject)
{
    const Math::Matrix4 matWorld = renderObject.transform.GetMatrix4();
    const Math::Matrix4 matView = mCamera->GetViewMatrix();
    const Math::Matrix4 matProj = mCamera->GetProjectionMatrix();

    
    transformData.World = Math::Transpose(matWorld);
    transformData.View = Math::Transpose(matView);
    transformData.Projection = Math::Transpose(matProj);
    transformData.CameraPos = mCamera->GetPosition();
    transformData.uvXOffset = 0.0f;

    mTransformBuffer.Update(transformData);

    ReflectionData reflectionData;
    reflectionData.WorldInverseTranspose = Math::Matrix4::InverseTranspose(matWorld);

    mReflectionBuffer.Update(reflectionData);

    renderObject.meshBuffer.Render();
}

void Reflection::Update()
{
    transformData.uvXOffset += 0.1f;
}

void Reflection::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}

void Reflection::SetReflectionMap(const Texture& reflectionMap)
{
    mReflectionMap = &reflectionMap;
}

void Reflection::SetTintColor(const Color& tintColor)
{
    mTintColor = tintColor;
}

void Reflection::DebugUI()
{
    if (ImGui::CollapsingHeader("ReflectionEffect",ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat3("Rotation", &transformData.uvXOffset, 0.1f, 20.0f);
    }
}
