cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

struct VertexShaderInput
{
	float3 pos : POSITION;
    float2 tex : TEXCOORD0;
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	float4 pos = float4(input.pos, 1.0f);

	// Transform the vertex position into projected space.
	//pos = mul(pos, model);
	//pos = mul(pos, view);
	//pos = mul(pos, projection);
	output.pos = pos;
	output.tex = input.tex;

	return output;
}
