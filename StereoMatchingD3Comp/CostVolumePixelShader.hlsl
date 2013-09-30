Texture2D Textures[2];
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
	float2 tex : TEXCOORD0;
	float disparity : DISPARITY;
};

struct PixelShaderOutput
{
	float4 color1 : SV_TARGET0;
	float4 color2 : SV_TARGET1;
	float4 color3 : SV_TARGET2;
	float4 color4 : SV_TARGET3;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET0
{
	PixelShaderOutput output;
	input.disparity = 1.0f;

	float4 px0_left = Textures[0].Sample(Sampler, input.tex - float2(dx, 0.0f));
	float4 px1_left = Textures[0].Sample(Sampler, input.tex);
	float4 px2_left = Textures[0].Sample(Sampler, input.tex + float2(dx, 0.0f));
	matrix<float, 4, 4> C;
	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float2 dispTex = input.tex - float2(dx * (input.disparity), 0.0f);
			float4 px0_right = Textures[1].Sample(Sampler, dispTex - float2(dx, 0.0f));
			float4 px1_right = Textures[1].Sample(Sampler, dispTex);
			float4 px2_right = Textures[1].Sample(Sampler, dispTex + float2(dx, 0.0f));

			float G = abs(
				0.149468010646888f * (px2_left[0] - px0_left[0] - px2_right[0] + px0_right[0]) + 
				0.293521537225561f * (px2_left[1] - px0_left[1] - px2_right[1] + px0_right[1]) + 
				0.057010452127552f * (px2_left[2] - px0_left[2] - px2_right[2] + px0_right[2])
				);

			float M = abs(
				px1_left[0] + px1_left[1] + px1_left[2] - px1_right[0] - px1_right[1] - px1_right[2]
			) / 3.0f;

			float tC = alpha * min(Tc, M) + (1 - alpha) * min(Tg, G);
		
			C[i][j] = tC;

			input.disparity += 1.0f;
		}
	}

	output.color1 = float4(C[0][0], C[0][1], C[0][2], C[0][3]);
	output.color2 = float4(C[1][0], C[1][1], C[1][2], C[0][3]);
	output.color3 = float4(C[2][0], C[2][1], C[2][2], C[0][3]);
	output.color4 = float4(C[3][0], C[3][1], C[3][2], C[0][3]);

	return output;
}
