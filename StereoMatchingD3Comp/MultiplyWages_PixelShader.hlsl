Texture2D TextureImage;
Texture2D TextureWages;
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
    float4 cost8  : SV_TARGET2;
    float4 cost12 : SV_TARGET3;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET
{
    PixelShaderOutput output;
    output.cost1 = float4(0.0f, 0.0f, 0.0f, 1.0f);
    output.cost4 = float4(0.0f, 0.0f, 0.0f, 1.0f);
    output.cost8 = float4(0.0f, 0.0f, 0.0f, 1.0f);
    output.cost12 = float4(0.0f, 0.0f, 0.0f, 1.0f);

    float4 I1 = TextureImage.Sample(Sampler, input.tex);
    float4 I2 = TextureWages.Sample(Sampler, input.tex);
    output.cost1[0] = I1[0] * I2[0];
    output.cost1[1] = I1[1] * I2[0];
    output.cost1[2] = I1[2] * I2[0];
    output.cost4[0] = I1[0] * I2[1];
    output.cost4[1] = I1[1] * I2[1];
    output.cost4[2] = I1[2] * I2[1];
    output.cost8[0] = I1[0] * I2[2];
    output.cost8[1] = I1[1] * I2[2];
    output.cost8[2] = I1[2] * I2[2];
    output.cost12[0] = I1[0] * I2[3];
    output.cost12[1] = I1[1] * I2[3];
    output.cost12[2] = I1[2] * I2[3];

    return output;
}
