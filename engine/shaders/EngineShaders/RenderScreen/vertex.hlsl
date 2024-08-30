struct VSInput
{
    float2 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
};

VSOutput Main(VSInput input)
{
    VSOutput outVal;
    outVal.position = float4(input.position, 0, 1);
    outVal.uv=input.uv;
    return outVal;
}