#pragma once

#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "Material.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "Texture.h"
#include "RenderTarget.h"

namespace KTEngine::Graphics
{
	class Camera;
	struct RenderObject;

    class Reflection final
    {
    public:
        void Initialize();
        void Terminate();
        void Begin();
        void End();
        void Render(const RenderObject& renderObject);
        void SetCamera(const Camera& camera);
        void SetReflectionMap(const Texture& reflectionMap);
        void SetTintColor(const Color& tintColor);
        void DebugUI();
        void Update();
        RenderTarget mTargets[6];
        RenderTarget mTarget;
    private:
        struct TransformData
        {
            Math::Matrix4 World;
            Math::Matrix4 View;
            Math::Matrix4 Projection;
            Math::Vector3 CameraPos;
            float uvXOffset = 0.0f;
        };

        struct ReflectionData
        {
            Math::Matrix4 WorldInverseTranspose;
        };

        using TransformBuffer = TypedConstantBuffer<TransformData>;
        TransformBuffer mTransformBuffer;
        TransformData transformData;
        using ReflectionBuffer = TypedConstantBuffer<ReflectionData>;
        ReflectionBuffer mReflectionBuffer;

        Texture mSkybox;
        
        VertexShader mVertexShader;
        PixelShader mPixelShader;
        Sampler mSampler;

        

        const Camera* mCamera = nullptr;
        const Texture* mReflectionMap = nullptr;
        Color mTintColor = Colors::White;
    };
}