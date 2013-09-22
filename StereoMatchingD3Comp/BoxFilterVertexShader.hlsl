cbuffer ConstantParametersBuffer
{
	const float alpha;
	const float Tc;
	const float Tg;
	const float dx;
};

struct VertexShaderInput
{
	float3 pos : POSITION;
    float2 tex : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;

	output.pos = float4(input.pos, 1.0f);
	output.tex = input.tex;

	return output;
}
