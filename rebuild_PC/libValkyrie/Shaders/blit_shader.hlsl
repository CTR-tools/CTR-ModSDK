#if defined(D3D9) || defined(GXM)
#define SV_TARGET COLOR0
#endif

#ifdef GXM
#define Texture2D sampler2D
#define uint4 int4
#define uint int
#endif

struct VS_INPUT {
#ifdef D3D9
	float4 a_position : POSITION;
	float4 a_texcoord : TEXCOORD0;
#else
	int4 a_position  : POSITION;
	uint4 a_texcoord : TEXCOORD0;
#endif
};

struct VS_OUTPUT {
#if defined(D3D9) || defined(GXM)
	float4 v_position  : POSITION;
#else
	float4 v_position  : SV_POSITION;
#endif
	float4 v_texcoord  : TEXCOORD0;
};

#ifdef VERTEX
	VS_OUTPUT main(VS_INPUT In) {
		VS_OUTPUT Out;
		Out.v_texcoord = In.a_texcoord * float4(8.0 / 1024.0, 8.0 / 512.0, 0.0, 0.0);
		Out.v_position = float4(In.a_position.xy, 0.0, 1.0);
		return Out;
	}
#else

#if defined(D3D9)
	SamplerState s_texture : register(s0);
	SamplerState s_lut : register(s1);
#elif defined(GXM)

#else
	SamplerState samplerState : register(s0);
	SamplerState samplerStateLUT : register(s1);
	Texture2D s_texture : register(t0);
	Texture2D s_lut : register(t1);
#endif

#if defined(GXM)
	float4 main(VS_OUTPUT In, uniform sampler2D s_texture : TEXUNIT0, uniform sampler2D s_lut : TEXUNIT1) {
#else
	float4 main(VS_OUTPUT In) : SV_TARGET {
#endif
#if defined(D3D9)
		float2 color_rg = tex2D(s_texture, In.v_texcoord.xy).ra;
		float4 color = tex2D(s_lut, color_rg).bgra;
#elif defined(GXM)
		float2 color_rg = tex2D(s_texture, In.v_texcoord.xy).rg;
		float4 color = tex2D(s_lut, color_rg);
#else
		float2 color_rg = s_texture.Sample(samplerState, In.v_texcoord.xy).rg;
		float4 color = s_lut.Sample(samplerStateLUT, color_rg);
#endif
		
		color.a = 1.0;

		return color;
	}
#endif
