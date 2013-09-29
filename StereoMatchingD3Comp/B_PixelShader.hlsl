Texture2D Textures[11];

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
	float4 b1  : SV_TARGET0;
	float4 b2  : SV_TARGET0;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET
{
	PixelShaderOutput output;
	
	float4 i = Textures[0].Sample(Sampler, input.tex);
	float4 d = Textures[1].Sample(Sampler, input.tex);

	float4 a = Textures[3].Sample(Sampler, input.tex);
	output.b1[0] = d[0] - a[0] * i[0] - a[1] * i[1] - a[2] * i[2];
	a = Textures[4].Sample(Sampler, input.tex);
	output.b1[1] = d[1] - a[0] * i[0] - a[1] * i[1] - a[2] * i[2];
	a = Textures[5].Sample(Sampler, input.tex);
	output.b1[2] = d[2] - a[0] * i[0] - a[1] * i[1] - a[2] * i[2];
	a = Textures[6].Sample(Sampler, input.tex);
	output.b1[3] = d[3] - a[0] * i[0] - a[1] * i[1] - a[2] * i[2];

	d = Textures[2].Sample(Sampler, input.tex);

	a = Textures[7].Sample(Sampler, input.tex);
	output.b2[0] = d[0] - a[0] * i[0] - a[1] * i[1] - a[2] * i[2];
	a = Textures[8].Sample(Sampler, input.tex);
	output.b2[1] = d[1] - a[0] * i[0] - a[1] * i[1] - a[2] * i[2];
	a = Textures[9].Sample(Sampler, input.tex);
	output.b2[2] = d[2] - a[0] * i[0] - a[1] * i[1] - a[2] * i[2];
	a = Textures[10].Sample(Sampler, input.tex);
	output.b2[3] = d[3] - a[0] * i[0] - a[1] * i[1] - a[2] * i[2];

	return output;
}
