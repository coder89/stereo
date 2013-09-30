Texture2D Texture;

SamplerState Sampler;

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
    float3 tmp = Texture.Sample(Sampler, input.tex);
    return float4(tmp, 1.0f);
}