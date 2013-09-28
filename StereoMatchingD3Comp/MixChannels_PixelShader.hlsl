Texture2D Texture[2];
SamplerState Sampler;

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

struct PixelShaderOutput
{
    float4 img1_RR_RG_RB  : SV_TARGET0;
    float4 img1_GG_GB_BB  : SV_TARGET1;
    float4 img2_RR_RG_RB  : SV_TARGET2;
    float4 img2_GG_GB_BB  : SV_TARGET3;
};

PixelShaderOutput main(PixelShaderInput input) : SV_TARGET
{
    PixelShaderOutput output;
    output.img1_RR_RG_RB[3] = 1.0f;
    output.img1_GG_GB_BB[3] = 1.0f;
    output.img2_RR_RG_RB[3] = 1.0f;
    output.img2_GG_GB_BB[3] = 1.0f;

    float4 pixel = Texture[0].Sample(Sampler, input.tex);

    output.img1_RR_RG_RB[0] = pixel[0] * pixel[0];
    output.img1_RR_RG_RB[1] = pixel[0] * pixel[1];
    output.img1_RR_RG_RB[2] = pixel[0] * pixel[2];

    output.img1_GG_GB_BB[0] = pixel[1] * pixel[1];
    output.img1_GG_GB_BB[1] = pixel[1] * pixel[2];
    output.img1_GG_GB_BB[2] = pixel[2] * pixel[2];

    pixel = Texture[1].Sample(Sampler, input.tex);

    output.img2_RR_RG_RB[0] = pixel[0] * pixel[0];
    output.img2_RR_RG_RB[1] = pixel[0] * pixel[1];
    output.img2_RR_RG_RB[2] = pixel[0] * pixel[2];

    output.img2_GG_GB_BB[0] = pixel[1] * pixel[1];
    output.img2_GG_GB_BB[1] = pixel[1] * pixel[2];
    output.img2_GG_GB_BB[2] = pixel[2] * pixel[2];

    return output;
}
