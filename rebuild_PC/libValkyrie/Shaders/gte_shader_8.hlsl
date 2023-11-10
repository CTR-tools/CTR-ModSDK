#if defined (D3D9) || defined(GXM)
	#define SV_TARGET COLOR0

#if defined(D3D9)	
	#define ARG_VPOS ,float2 coord : VPOS
#elif defined(GXM)
	#define ARG_VPOS ,float2 coord : WPOS///@FIXME VPOS!
#endif
	#define FRAG_COORD coord.xy
#else
	#define FRAG_COORD In.v_position.xy
	#define ARG_VPOS
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
	float4 a_color    : COLOR0;
#else
	int4 a_position   : POSITION;
	uint4 a_texcoord  : TEXCOORD0;
	float4 a_color    : COLOR0;
#endif
};

struct VS_OUTPUT {
#if defined(D3D9) || defined(GXM)
	float4 v_position  : POSITION;
#else
	float4 v_position  : SV_POSITION;
#endif
	float4 v_texcoord  : TEXCOORD0;
	float4 v_color     : TEXCOORD1;
	float4 v_page_clut : TEXCOORD2;
};

#ifdef VERTEX
#if defined(D3D12)
	cbuffer ConstantBuffer : register(b0)
	{
		float4x4 Projection;
	};
#elif defined(GXM)
	uniform float4x4 Projection : register(c0);
#else
	float4x4 Projection : register(c0);
#endif

	VS_OUTPUT main(VS_INPUT In) {
		VS_OUTPUT Out;
		Out.v_texcoord     = In.a_texcoord;
		Out.v_color        = In.a_color;
		Out.v_color.xyz   *= In.a_texcoord.z;
		Out.v_page_clut.x  = frac (In.a_position.z / 16.0) * 1024.0;
		Out.v_page_clut.y  = floor(In.a_position.z / 16.0) * 256.0;
		Out.v_page_clut.z  = frac (In.a_position.w / 64.0);
		Out.v_page_clut.w  = floor(In.a_position.w / 64.0) / 512.0;
		Out.v_position     = mul(Projection, float4(In.a_position.xy, 0.0, 1.0));
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
	float4 main(VS_OUTPUT In ARG_VPOS, uniform sampler2D s_texture : TEXUNIT0, uniform sampler2D s_lut : TEXUNIT1) {
#else
	float4 main(VS_OUTPUT In ARG_VPOS) : SV_TARGET {
#endif
		float2 uv = (In.v_texcoord.xy * float2(0.5, 1.0) + In.v_page_clut.xy) * float2(1.0 / 1024.0, 1.0 / 512.0);
#if defined(D3D9)
		float2 comp = tex2D(s_texture, uv).ra;
#elif defined(GXM)
		float2 comp = tex2D(s_texture, uv).rg;
#else
		float2 comp = s_texture.Sample(samplerState, uv).rg;
#endif

		float2 clut_pos = In.v_page_clut.zw;
		clut_pos.x += comp[int(fmod(In.v_texcoord.x, 2.0))] * 255.0 / 1024.0;
#if defined(D3D9)
		float2 clut_color = tex2D(s_texture, clut_pos).ra;
#elif defined(GXM)
		float2 clut_color = tex2D(s_texture, clut_pos).rg;
#else
		float2 clut_color = s_texture.Sample(samplerState, clut_pos).rg;
#endif

		if(clut_color.x == 0.0 && clut_color.y == 0.0)
		{
#if !defined(XENON)
			discard;
#endif
		}
#if defined(D3D9)
		float4 color = tex2D(s_lut, clut_color).bgra;
#elif defined(GXM)
		float4 color = tex2D(s_lut, clut_color);
#else		
		float4 color = s_lut.Sample(samplerStateLUT, clut_color);
#endif
		color = color * In.v_color;
		float4x4 dither = float4x4(
			-4.0,  +0.0,  -3.0,  +1.0,
			+2.0,  -2.0,  +3.0,  -1.0,
			-3.0,  +1.0,  -4.0,  +0.0,
			+3.0,  -1.0,  +2.0,  -2.0) / 255.0;
		int2 dc = int2(frac(FRAG_COORD / 4.0) * 4.0);
		color.xyz += dither[dc.x][dc.y] * In.v_texcoord.w;

		return color;
	}
#endif
