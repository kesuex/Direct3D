
struct vertexIN
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct vertexOUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

cbuffer ConstatntBuffer 
{
    matrix World;
    matrix View;
    matrix Projection;
};

vertexOUT main(vertexIN input)
{
    vertexOUT output;
    output.position = mul(float4(input.position, 1.0f),World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
    output.color = input.color;
    return output;
}