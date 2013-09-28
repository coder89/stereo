Texture2D Texture[2];
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
    float4 cost4  : SV_TARGET1;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET
{
    PixelShaderOutput output;
    output.cost1 = float4(0,0,0,0);
    output.cost4 = float4(0,0,0,0);

    float2 tmp = input.tex - float2(r * dx, 0.0f);
    [unroll(20)]
    for (int i = -r; i <= r; ++i)
    {
        tmp.x += dx;
        output.cost1 += Texture[0].Sample(Sampler, tmp);
    }
    
    tmp = input.tex - float2(r * dx, 0.0f);
    [unroll(20)]
    for (int i = -r; i <= r; ++i)
    {
        tmp.x += dx;
        output.cost4 += Texture[1].Sample(Sampler, tmp);
    }

    float W = 2 * r + 1;
    output.cost1 /= float4(W,W,W,W);
    output.cost4 /= float4(W,W,W,W);

    return output;
}
