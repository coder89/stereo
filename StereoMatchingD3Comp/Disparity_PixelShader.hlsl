Texture2D Q[4];

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
	float4 result  : SV_TARGET0;
};

float2 min_disparity(float4 q)
{
	//float2 result = float2(1, q[0]);

	//for (int i = 1; i < 4; ++i)
	//{
	//	for (int j = i; j < 4; ++j)
	//	{
	//		if (result[1] > q[j])
	//		{
	//			result[1] = q[j];
	//			result[0] = j+1;
	//		}
	//	}
	//}

	//return result;

	if (q[0] <= q[1])
	{
		if (q[0] <= q[2])
		{
			if (q[0] <= q[3])
				return float2(1, q[0]);
			else
				return float2(4, q[3]);
		}
		else 
		{
			if (q[2] <= q[3])
				return float2(3, q[2]);
			else
				return float2(4, q[3]);
		}
	}
	else 
	{
		if (q[1] <= q[2])
		{
			if (q[1] <= q[3])
				return float2(2, q[1]);
			else 
			{
				if (q[3] < q[2])
					return float2(4, q[3]);
				else
					return float2(3, q[2]);
			}
		}
		else 
		{
			if (q[2] <= q[3])
				return float2(3, q[2]);
			else
				return float2(4, q[3]);
		}
	}
}

float4 main(PixelShaderInput input) : SV_TARGET
{
	float2 r1 = min_disparity(Q[0].Sample(Sampler, input.tex));
		float2 r2 = min_disparity(Q[1].Sample(Sampler, input.tex));
		float2 r3 = min_disparity(Q[2].Sample(Sampler, input.tex));
		float2 r4 = min_disparity(Q[3].Sample(Sampler, input.tex));

		uint4 d = uint4(r1[0], r2[0], r3[0], r4[0]);
		float2 r5 = min_disparity(float4(r1[1], r2[1], r3[1], r4[1]));

		float result = d[r5[0]-1] + (r5[0] - 1) * 4.0f;

	return float4(result / 16.0f, result / 16.0f, result / 16.0f, 1.0f);
}
