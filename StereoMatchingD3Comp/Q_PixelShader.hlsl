Texture2D Texture[6];

SamplerState Sampler;

cbuffer ConstantParametersBuffer
{
	// Algorithm parameters
	const float r;
	const float epsilon;
	const float alpha;
	const float sigma_s;
	const float sigma_c;
	const float Tc;
	const float Tg;

	// Image metrics
	float dx;				// Normalized pizel width
	float dy;				// Normalized pixel height
	float dz;				// Normalized pixel "thickness" in Z-axis => 1/dz = max_disparity
};

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

struct PixelShaderOutput
{
	float4 q  : SV_TARGET0;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET
{
	PixelShaderOutput output;
	
	float4 i = Texture[0].Sample(Sampler, input.tex);
	float4 b = Texture[5].Sample(Sampler, input.tex);

	float4 a = Texture[1].Sample(Sampler, input.tex);
	output.q[0] = a[0] * i[0] + a[1] * i[1] + a[2] * i[2] + b[0];

	a = Texture[2].Sample(Sampler, input.tex);
	output.q[1] = a[0] * i[0] + a[1] * i[1] + a[2] * i[2] + b[1];

	a = Texture[3].Sample(Sampler, input.tex);
	output.q[2] = a[0] * i[0] + a[1] * i[1] + a[2] * i[2] + b[2];

	a = Texture[4].Sample(Sampler, input.tex);
	output.q[3] = a[0] * i[0] + a[1] * i[1] + a[2] * i[2] + b[3];

	return output;
}
