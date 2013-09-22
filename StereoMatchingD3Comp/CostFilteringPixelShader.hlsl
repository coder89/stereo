Texture3D CostVolume;
Texture2D TextureLeft;
Texture2D TextureRight;

SamplerState Sampler;

cbuffer ConstantParametersBuffer
{
	const float alpha;
	const float Tc;
	const float Tg;
	const float dx;
};

cbuffer TextureProjectionConstantBuffer
{
	float disparity;
};

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 px0_left = TextureLeft.Sample(Sampler, input.tex - float2(dx, 0.0f));
	float4 px1_left = TextureLeft.Sample(Sampler, input.tex);
	float4 px2_left = TextureLeft.Sample(Sampler, input.tex + float2(dx, 0.0f));

	float4 px0_right = TextureRight.Sample(Sampler, input.tex - float2(dx, 0.0f));
	float4 px1_right = TextureRight.Sample(Sampler, input.tex);
	float4 px2_right = TextureRight.Sample(Sampler, input.tex + float2(dx, 0.0f));

	float G = abs(
					0.149468010646888f * (px2_left[0] - px0_left[0] - px2_right[0] + px0_right[0]) + 
					0.293521537225561f * (px2_left[1] - px0_left[1] - px2_right[1] + px0_right[1]) + 
					0.057010452127552f * (px2_left[2] - px0_left[2] - px2_right[2] + px0_right[2])
			     );

	float M = abs(
					px1_left[0] + px1_left[1] + px1_left[2] - px1_right[0] - px1_right[1] - px1_right[2]
				 );

	float C = alpha * min(Tc, M) + (1 - alpha) * min(Tg, G);

    return px0_left;
}
