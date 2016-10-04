cbuffer worldPosition : register(b0)
{
	float4x4 World;
	float4x4 Rotation;
};

struct VS_IN
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float3 Normal : NORMAL;
};

struct VS_OUT
{
	float4 PosInW : WORLDPOS;
	float4 NormalInW : NORMALINW;
	float2 Tex : TEXCOORD;
};

VS_OUT VS_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.PosInW = mul(float4(input.Pos, 1), World);
	output.NormalInW = normalize(mul(float4(input.Normal, 1), Rotation));
	output.Tex = input.Tex;

	return output;
}