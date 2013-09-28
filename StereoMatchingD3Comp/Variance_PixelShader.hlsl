Texture2D Texture[6];
SamplerState Sampler;

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

struct PixelShaderOutput
{
    float4 variance1_RR_RG_RB  : SV_TARGET0;
    float4 variance1_GG_GB_BB  : SV_TARGET1;
    float4 variance2_RR_RG_RB  : SV_TARGET2;
    float4 variance2_GG_GB_BB  : SV_TARGET3;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET
{
    PixelShaderOutput output;
    output.variance1_RR_RG_RB[3] = 1.0f;
    output.variance1_GG_GB_BB[3] = 1.0f;
    output.variance2_RR_RG_RB[3] = 1.0f;
    output.variance2_GG_GB_BB[3] = 1.0f;

    float4 mixedBox = Texture[0].Sample(Sampler, input.tex);
    float4 mean = Texture[2].Sample(Sampler, input.tex);
    
    output.variance1_RR_RG_RB[0] = mixedBox[0] - mean[0] * mean[0];
    output.variance1_RR_RG_RB[1] = mixedBox[1] - mean[0] * mean[1];
    output.variance1_RR_RG_RB[2] = mixedBox[2] - mean[0] * mean[2];

    mixedBox = Texture[1].Sample(Sampler, input.tex);
    output.variance1_GG_GB_BB[0] = mixedBox[0] - mean[1] * mean[1];
    output.variance1_GG_GB_BB[1] = mixedBox[1] - mean[1] * mean[2];
    output.variance1_GG_GB_BB[2] = mixedBox[2] - mean[2] * mean[2];
    
    mixedBox = Texture[3].Sample(Sampler, input.tex);
    mean = Texture[5].Sample(Sampler, input.tex);
    
    output.variance2_RR_RG_RB[0] = mixedBox[0] - mean[0] * mean[0];
    output.variance2_RR_RG_RB[1] = mixedBox[1] - mean[0] * mean[1];
    output.variance2_RR_RG_RB[2] = mixedBox[2] - mean[0] * mean[2];

    mixedBox = Texture[4].Sample(Sampler, input.tex);
    output.variance2_GG_GB_BB[0] = mixedBox[0] - mean[1] * mean[1];
    output.variance2_GG_GB_BB[1] = mixedBox[1] - mean[1] * mean[2];
    output.variance2_GG_GB_BB[2] = mixedBox[2] - mean[2] * mean[2];

    return output;
}
