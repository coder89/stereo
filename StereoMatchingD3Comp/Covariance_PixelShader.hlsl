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
    float4 cost1  : SV_TARGET0;
    float4 cost2  : SV_TARGET0;
    float4 cost3  : SV_TARGET0;
    float4 cost4  : SV_TARGET0;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET
{
    PixelShaderOutput output;
    output.cost1 = float4(0,0,0,1);
    output.cost2 = float4(0,0,0,1);
    output.cost3 = float4(0,0,0,1);
    output.cost4 = float4(0,0,0,1);

    float4 img = Texture[0].Sample(Sampler, input.tex);
    float4 cost = Texture[1].Sample(Sampler, input.tex);
    
    float4 imgCost = Texture[2].Sample(Sampler, input.tex);
    output.cost1[0] = imgCost[0] - img[0] * cost[0];
    output.cost1[1] = imgCost[1] - img[1] * cost[0];
    output.cost1[2] = imgCost[2] - img[2] * cost[0];

    imgCost = Texture[3].Sample(Sampler, input.tex);
    output.cost2[0] = imgCost[0] - img[0] * cost[1];
    output.cost2[1] = imgCost[1] - img[1] * cost[1];
    output.cost2[2] = imgCost[2] - img[2] * cost[1];

    imgCost = Texture[4].Sample(Sampler, input.tex);
    output.cost3[0] = imgCost[0] - img[0] * cost[2];
    output.cost3[1] = imgCost[1] - img[1] * cost[2];
    output.cost3[2] = imgCost[2] - img[2] * cost[2];

    imgCost = Texture[5].Sample(Sampler, input.tex);
    output.cost4[0] = imgCost[0] - img[0] * cost[3];
    output.cost4[1] = imgCost[1] - img[1] * cost[3];
    output.cost4[2] = imgCost[2] - img[2] * cost[3];

    output.cost1 = img;

    return output;
}
