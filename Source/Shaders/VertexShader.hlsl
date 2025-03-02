
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

vertexOUT main(vertexIN input)
{
    vertexOUT output;
    output.position = float4(input.position, 1.0f);
    output.color = input.color;
    return output;
}