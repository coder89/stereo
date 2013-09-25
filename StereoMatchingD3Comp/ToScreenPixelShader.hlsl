Texture3D Texture;

SamplerState Sampler;

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	//return float4(1,1,1,1);
	return Texture.Sample(Sampler, float3(input.tex, 1));
}