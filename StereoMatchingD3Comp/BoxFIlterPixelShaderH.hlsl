static const int r = 9;

Texture2D Texture;

SamplerState Sampler;

cbuffer ConstantParametersBuffer
{
	const float alpha;
	const float Tc;
	const float Tg;
	const float dx;
};

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 px = float4(0,0,0,0);

	for (int i = -r; i <= r; ++i)
	{
		px += Texture.Sample(Sampler, input.tex + float2(0.0f, i * dx));
	}
	
	float W = 2 * r + 1;
	px[0] /= W;
	px[1] /= W;
	px[2] /= W;
	px[3] /= W;

	return px;
}
