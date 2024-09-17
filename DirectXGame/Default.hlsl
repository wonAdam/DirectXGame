cbuffer ConstantBuffer
{
    float4x4 matFinal;
}

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};


VOut VS(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;

    output.position = mul(matFinal, position);
    output.color = color;

    return output;
}

float4 PS(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}