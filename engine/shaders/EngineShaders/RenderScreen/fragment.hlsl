struct PSInput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
};

struct PSOutput
{
    float4 colour : SV_Target0;
};

SamplerState linearsampler : register(s0);
Texture2D Texture : register(t0);

PSOutput Main(PSInput input)
{
    PSOutput output = { Texture.Sample(linearsampler, input.uv) };
    return output;
}