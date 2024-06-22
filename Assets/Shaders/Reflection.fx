cbuffer TransformBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float3 CameraPos;
    float uvXOffset;
}

cbuffer ReflectionBuffer : register(b1)
{
    float3x3 WorldInverseTranspose;
}

float4 TintColor = float4(1, 1, 1, 1);

Texture2D directionX : register(t0);

SamplerState SkyboxSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float3 reflection : TEXCOORD;
    float3 worldPos : TEXCOORD1;
    float normal : TEXCOORD2;
    float2 texcoord : TEXCOORD3;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;

    float4 worldPos = mul(float4(input.position, 1.0f), World);
    output.worldPos = worldPos.xyz;

    float4 viewPos = mul(worldPos, View);
    output.position = mul(viewPos, Projection);

    output.normal = normalize(mul(input.normal, WorldInverseTranspose));
    output.texcoord = input.texcoord;
    output.texcoord.x += uvXOffset;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float3 viewDirection = normalize(CameraPos - input.worldPos);
    float3 reflection = reflect(-viewDirection, input.normal);
    float4 reflectionColor = directionX.Sample(SkyboxSampler, input.texcoord);
    
    float4 baseColor = TintColor;
    float4 finalColor = lerp(baseColor, reflectionColor, 0.5f);
    
    return finalColor;
}

technique10 Reflection
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_4_0, VS()));
        SetPixelShader(CompileShader(ps_4_0, PS()));
    }
}


