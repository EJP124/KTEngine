cbuffer TransformBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    float3 CameraPos;
}

struct VS_INPUT
{
    float4 position : POSITION;
    float3 normal : NORMAL;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 reflected : TEXCOORD0;
};

VS_INPUT ReflectionVertexShader(VS_INPUT input)
{
    VS_OUTPUT output;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    float4 worldPosition = mul(input.position, worldMatrix);
    float4 viewPosition = mul(worldPosition, viewMatrix);
    output.position = mul(viewPosition, projectionMatrix);

    // Calculate the normal in world space
    float3 worldNormal = mul(input.normal, (float3x3) worldMatrix);

    // Calculate the reflected vector
    float3 incident = worldPosition.xyz - CameraPos;
    output.reflected = reflect(incident, worldNormal);

    return output;
}

TextureCube reflectionMap;
SamplerState SampleType;

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 reflected : TEXCOORD0;
};
float4 ReflectionPixelShader(PS_INPUT input) : SV_TARGET
{
    // Sample the cube map using the reflected vector
    return reflectionMap.Sample(SampleType, input.reflected);
}