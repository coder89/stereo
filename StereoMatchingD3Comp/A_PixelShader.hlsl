Texture2D Textures[6];

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
	float4 a1  : SV_TARGET0;
	float4 a2  : SV_TARGET0;
	float4 a3  : SV_TARGET0;
	float4 a4  : SV_TARGET0;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET
{
	PixelShaderOutput output;
	
	float4 v_RR_RG_RB = Textures[0].Sample(Sampler, input.tex);
	float4 v_GG_GB_BB = Textures[1].Sample(Sampler, input.tex);

	float a = v_RR_RG_RB[0] + 0.0001f;
	float b = v_RR_RG_RB[1];
	float c = v_RR_RG_RB[2];
	float d = v_GG_GB_BB[0] + 0.0001f;
	float e = v_GG_GB_BB[1];
	float f = v_GG_GB_BB[2] + 0.0001f;

	float M = 1 / ( -a*d*f + a*e*e + b*b*f -2*b*c*e + c*c*d );

	float na = M * (e*e-d*f);
	float nb = M * (b*f-c*e);
	float nc = M * (c*d-b*e);
	float nd = M * (c*c-a*f);
	float ne = M * (a*e-b*c);
	float nf = M * (b*b-a*d);

	matrix<float, 3, 3> v = { na, nb, nc,
							  nb, nd, ne,
							  nc, ne, nf};

	float4 cov = Textures[2].Sample(Sampler, input.tex);
	float3 tmp = mul(cov, v);
	output.a1[0] = tmp[0];
	output.a1[1] = tmp[1];
	output.a1[2] = tmp[2];
	output.a1[3] = 1.0f;
	
	cov = Textures[3].Sample(Sampler, input.tex);
	tmp = mul(cov, v);
	output.a2[0] = tmp[0];
	output.a2[1] = tmp[1];
	output.a2[2] = tmp[2];
	output.a2[3] = 1.0f;

	cov = Textures[4].Sample(Sampler, input.tex);
	tmp = mul(cov, v);
	output.a3[0] = tmp[0];
	output.a3[1] = tmp[1];
	output.a3[2] = tmp[2];
	output.a3[3] = 1.0f;

	cov = Textures[5].Sample(Sampler, input.tex);
	tmp = mul(cov, v);
	output.a4[0] = tmp[0];
	output.a4[1] = tmp[1];
	output.a4[2] = tmp[2];
	output.a4[3] = 1.0f;
	
	return output;
}
