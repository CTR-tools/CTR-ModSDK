#include "LIBGPU.H"
#include "EMULATOR_RENDER_OGL.H"
#include "Core/Debug/EMULATOR_LOG.H"
#include "Core/Render/EMULATOR_RENDER_COMMON.H"
#include <stdio.h>
#include <stdlib.h>

#if defined(OGL)

#if defined(__APPLE__) || defined(__linux__)
#include <SDL_opengl.h>
#else
#include <gl/GL.h>

// hint to the driver to use discrete GPU
extern "C" {
	// NVIDIA
	__declspec(dllexport) int NvOptimusEnablement = 1;
	// AMD
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

#if defined(_WINDOWS)
HWND g_overrideHWND = NULL;
#endif

PFNGLCREATEPROGRAMPROC              glCreateProgram;
PFNGLDELETEPROGRAMPROC              glDeleteProgram;
PFNGLLINKPROGRAMPROC                glLinkProgram;
PFNGLUSEPROGRAMPROC                 glUseProgram;
PFNGLGETPROGRAMINFOLOGPROC          glGetProgramInfoLog;
PFNGLCREATESHADERPROC               glCreateShader;
PFNGLDELETESHADERPROC               glDeleteShader;
PFNGLSHADERSOURCEPROC               glShaderSource;
PFNGLATTACHSHADERPROC               glAttachShader;
PFNGLCOMPILESHADERPROC              glCompileShader;
PFNGLGETSHADERINFOLOGPROC           glGetShaderInfoLog;
PFNGLGETUNIFORMLOCATIONPROC         glGetUniformLocation;
PFNGLUNIFORM1IPROC                  glUniform1i;
PFNGLUNIFORMMATRIX4FVPROC           glUniformMatrix4fv;
PFNGLBINDATTRIBLOCATIONPROC         glBindAttribLocation;
PFNGLENABLEVERTEXATTRIBARRAYPROC    glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC   glDisableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC        glVertexAttribPointer;
PFNGLGETPROGRAMIVPROC               glGetProgramiv;
PFNGLDELETEVERTEXARRAYSPROC					 glDeleteVertexArrays;
PFNGLGENFRAMEBUFFERSPROC                     glGenFramebuffers;
PFNGLBINDFRAMEBUFFERPROC                     glBindFramebuffer;
PFNGLGENRENDERBUFFERSPROC                    glGenRenderbuffers;
PFNGLBINDRENDERBUFFERPROC                    glBindRenderbuffer;
PFNGLFRAMEBUFFERTEXTURE2DPROC                glFramebufferTexture2D;
PFNGLFRAMEBUFFERRENDERBUFFERPROC             glFramebufferRenderbuffer;
PFNGLRENDERBUFFERSTORAGEPROC                 glRenderbufferStorage;
PFNGLCHECKFRAMEBUFFERSTATUSPROC              glCheckFramebufferStatus;
PFNGLDELETEFRAMEBUFFERSPROC                  glDeleteFramebuffers;
PFNGLDELETERENDERBUFFERSPROC                 glDeleteRenderbuffers;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;
PFNGLGENBUFFERSARBPROC              glGenBuffers;
PFNGLDELETEBUFFERSARBPROC           glDeleteBuffers;
PFNGLBINDBUFFERARBPROC              glBindBuffer;
PFNGLBUFFERDATAARBPROC              glBufferData;
PFNGLBUFFERSUBDATAARBPROC           glBufferSubData;
PFNGLGENVERTEXARRAYSPROC            glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC            glBindVertexArray;
PFNGLDRAWELEMENTSBASEVERTEXPROC     glDrawElementsBaseVertex;
PFNGLBLENDEQUATIONEXTPROC			glBlendEquationEXT;
PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB2;
PFNGLBLENDCOLOREXTPROC				glBlendColorEXT;

#define glBlendColor glBlendColorEXT
#define glActiveTexture glActiveTextureARB2
#define glBlendEquation glBlendEquationEXT

extern void Emulator_DoPollEvent();
extern void Emulator_WaitForTimestep(int count);
extern void Emulator_GenerateCommonTextures();
extern void Emulator_CreateGlobalShaders();
extern void Emulator_DestroyTextures();
extern void Emulator_DestroyGlobalShaders();
extern void Emulator_CreateVertexBuffer();
extern void Emulator_CreateIndexBuffer();

const char* renderBackendName = "OpenGL 3.3";

GLuint dynamic_vertex_buffer;
GLuint dynamic_vertex_array;

GLuint dynamic_index_buffer;

SDL_Window* g_window = NULL;

int g_overrideWidth = -1;
int g_overrideHeight = -1;

GLint u_Projection;

#define GTE_DISCARD\
	"		if (color_rg.x + color_rg.y == 0.0) { discard; }\n"

#define GTE_DECODE_RG\
	"		fragColor = texture2D(s_lut, color_rg);\n"

#define GTE_FETCH_DITHER_FUNC\
	"		mat4 dither = mat4(\n"\
	"			-4.0,  +0.0,  -3.0,  +1.0,\n"\
	"			+2.0,  -2.0,  +3.0,  -1.0,\n"\
	"			-3.0,  +1.0,  -4.0,  +0.0,\n"\
	"			+3.0,  -1.0,  +2.0,  -2.0) / 255.0;\n"\
	"		vec3 DITHER(const ivec2 dc) { \n"\
	"		for (int i = 0; i < 4; i++) {"\
	"			for (int j = 0; j < 4; j++) {"\
	"			if(i == dc.x && j == dc.y) {"\
	"				return vec3(dither[i][j] * v_texcoord.w); }\n"\
	"				}"\
	"			}"\
	"		}"

#define GTE_DITHERING\
	"		fragColor *= v_color;\n"\
	"		ivec2 dc = ivec2(fract(gl_FragCoord.xy / 4.0) * 4.0);\n"\
	"		fragColor.xyz += DITHER(dc);\n"

#define GTE_FETCH_VRAM_FUNC\
		"	uniform sampler2D s_texture;\n"\
		"	uniform sampler2D s_lut;\n"\
		"	vec2 VRAM(vec2 uv) { return texture2D(s_texture, uv).rg; }\n"

#if defined(PGXP)
#define GTE_PERSPECTIVE_CORRECTION \
		"		gl_Position.z = a_z;\n" \
		"		gl_Position *= a_w;\n"
#else
#define GTE_PERSPECTIVE_CORRECTION
#endif

const char* gte_shader_4 =
"varying vec4 v_texcoord;\n"
"varying vec4 v_color;\n"
"varying vec4 v_page_clut;\n"
"#ifdef VERTEX\n"
"	attribute vec4 a_position;\n"
"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
"	attribute vec4 a_color;\n"
"	attribute float a_z;\n"
"	attribute float a_w;\n"
"	uniform mat4 Projection;\n"
"	void main() {\n"
"		v_texcoord = a_texcoord;\n"
"		v_color = a_color;\n"
"		v_color.xyz *= a_texcoord.z;\n"
"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"
"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"
"		v_page_clut.z = fract(a_position.w / 64.0);\n"
"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"
"		gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
GTE_PERSPECTIVE_CORRECTION
"	}\n"
"#else\n"
GTE_FETCH_DITHER_FUNC
GTE_FETCH_VRAM_FUNC
"	void main() {\n"
"		vec2 uv = (v_texcoord.xy * vec2(0.25, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
"		vec2 comp = VRAM(uv);\n"
"		int index = int(fract(v_texcoord.x / 4.0 + 0.0001) * 4.0);\n"
"\n"
"		float v = 0.0;\n"
"		if(index / 2 == 0) { \n"
"			v = comp[0] * (255.0 / 16.0);\n"
"		} else {	\n"
"			v = comp[1] * (255.0 / 16.0);\n"
"		}\n"
"		float f = floor(v);\n"
"\n"
"		vec2 c = vec2( (v - f) * 16.0, f );\n"
"\n"
"		vec2 clut_pos = v_page_clut.zw;\n"
"		clut_pos.x += mix(c[0], c[1], fract(float(index) / 2.0) * 2.0) / 1024.0;\n"
"		vec2 color_rg = VRAM(clut_pos);\n"
GTE_DISCARD
GTE_DECODE_RG
GTE_DITHERING
"	}\n"
"#endif\n";

const char* gte_shader_8 =
"varying vec4 v_texcoord;\n"
"varying vec4 v_color;\n"
"varying vec4 v_page_clut;\n"
"#ifdef VERTEX\n"
"	attribute vec4 a_position;\n"
"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
"	attribute vec4 a_color;\n"
"	attribute float a_z;\n"
"	attribute float a_w;\n"
"	uniform mat4 Projection;\n"
"	void main() {\n"
"		v_texcoord = a_texcoord;\n"
"		v_color = a_color;\n"
"		v_color.xyz *= a_texcoord.z;\n"
"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"
"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"
"		v_page_clut.z = fract(a_position.w / 64.0);\n"
"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"
"		gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
GTE_PERSPECTIVE_CORRECTION
"	}\n"
"#else\n"
GTE_FETCH_VRAM_FUNC
GTE_FETCH_DITHER_FUNC
"	void main() {\n"
"		vec2 uv = (v_texcoord.xy * vec2(0.5, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
"		vec2 comp = VRAM(uv);\n"
"\n"
"		vec2 clut_pos = v_page_clut.zw;\n"
"		int index = int(mod(v_texcoord.x, 2.0));\n"
"		if(index == 0) { \n"
"			clut_pos.x += comp[0] * 255.0 / 1024.0;\n"
"		} else {	\n"
"			clut_pos.x += comp[1] * 255.0 / 1024.0;\n"
"		}\n"
"		vec2 color_rg = VRAM(clut_pos);\n"
GTE_DISCARD
GTE_DECODE_RG
GTE_DITHERING
"	}\n"
"#endif\n";

const char* gte_shader_16 =
"varying vec4 v_texcoord;\n"
"varying vec4 v_color;\n"
"#ifdef VERTEX\n"
"	attribute vec4 a_position;\n"
"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
"	attribute vec4 a_color;\n"
"	attribute float a_z;\n"
"	attribute float a_w;\n"
"	uniform mat4 Projection;\n"
"	void main() {\n"
"		vec2 page\n;"
"		page.x = fract(a_position.z / 16.0) * 1024.0\n;"
"		page.y = floor(a_position.z / 16.0) * 256.0;\n;"
"		v_texcoord = a_texcoord;\n"
"		v_texcoord.xy += page;\n"
"		v_texcoord.xy *= vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
"		v_color = a_color;\n"
"		v_color.xyz *= a_texcoord.z;\n"
"		gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
GTE_PERSPECTIVE_CORRECTION
"	}\n"
"#else\n"
GTE_FETCH_VRAM_FUNC
GTE_FETCH_DITHER_FUNC
"	void main() {\n"
"		vec2 color_rg = VRAM(v_texcoord.xy);\n"
GTE_DISCARD
GTE_DECODE_RG
GTE_DITHERING
"	}\n"
"#endif\n";

const char* blit_shader =
"varying vec4 v_texcoord;\n"
"#ifdef VERTEX\n"
"	attribute vec4 a_position;\n"
"	attribute vec4 a_texcoord;\n"
"	void main() {\n"
"		v_texcoord = a_texcoord * vec4(8.0 / 1024.0, 8.0 / 512.0, 0.0, 0.0);\n"
"		gl_Position = vec4(a_position.xy, 0.0, 1.0);\n"
"	}\n"
"#else\n"
GTE_FETCH_VRAM_FUNC
"	void main() {\n"
"		vec2 color_rg = VRAM(v_texcoord.xy);\n"
GTE_DECODE_RG
"	}\n"
"#endif\n";

void Shader_CheckShaderStatus(GLuint shader)
{
	char info[1024];
	glGetShaderInfoLog(shader, sizeof(info), NULL, info);
	if (info[0] && strlen(info) > 8)
	{
		eprinterr("%s\n", info);
		eassert(FALSE);
	}
}

void Shader_CheckProgramStatus(GLuint program)
{
	char info[1024];
	glGetProgramInfoLog(program, sizeof(info), NULL, info);
    
    
	if (info[0] && strlen(info) > 8)
	{
		eprinterr("%s\n", info);
#if !defined(__APPLE__)
		eassert(FALSE);
#endif
	}
}

ShaderID Shader_Compile(const char* source)
{
	const char* GLSL_HEADER_VERT =
		"#version 330\n"
		"#define VERTEX\n"
		"#define varying   out\n"
		"#define attribute in\n"
		"#define texture2D texture\n";

	const char* GLSL_HEADER_FRAG =
		"#version 330\n"
		"#define varying     in\n"
		"#define texture2D   texture\n"
		"out vec4 fragColor;\n";

	const char* vs_list[] = { GLSL_HEADER_VERT, source };
	const char* fs_list[] = { GLSL_HEADER_FRAG, source };

	ShaderID shader;

	shader.program = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 2, vs_list, NULL);
	glCompileShader(vertexShader);
	Shader_CheckShaderStatus(vertexShader);
	glAttachShader(shader.program, vertexShader);
	glDeleteShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 2, fs_list, NULL);
	glCompileShader(fragmentShader);
	Shader_CheckShaderStatus(fragmentShader);
	glAttachShader(shader.program, fragmentShader);
	glDeleteShader(fragmentShader);

	glBindAttribLocation(shader.program, a_position, "a_position");
	glBindAttribLocation(shader.program, a_texcoord, "a_texcoord");
	glBindAttribLocation(shader.program, a_color, "a_color");

#if defined(PGXP)
	glBindAttribLocation(shader.program, a_z, "a_z");
	glBindAttribLocation(shader.program, a_w, "a_w");
#endif

	glLinkProgram(shader.program);
	Shader_CheckProgramStatus(shader.program);

	glUseProgram(shader.program);
	shader.textures[SLOT_VRAM] = glGetUniformLocation(shader.program, "s_texture");
	shader.textures[SLOT_LUT] = glGetUniformLocation(shader.program, "s_lut");
	
	glUniform1i(shader.textures[SLOT_VRAM], SLOT_VRAM);
	glUniform1i(shader.textures[SLOT_LUT], SLOT_LUT);

	glUseProgram(0);

	return shader;
}

void Emulator_DestroyVertexBuffer()
{
	glDeleteBuffers(1, &dynamic_vertex_buffer);
	glDeleteVertexArrays(1, &dynamic_vertex_array);

	dynamic_vertex_buffer = 0;
	dynamic_vertex_array = 0;
}

void Emulator_DestroyIndexBuffer()
{
	glDeleteBuffers(1, &dynamic_index_buffer);

	dynamic_index_buffer = 0;
}

void Emulator_ResetDevice(int recreate)
{
	if (!g_resettingDevice)
	{
		g_resettingDevice = TRUE;

		Emulator_DestroyVertexBuffer();

		Emulator_DestroyIndexBuffer();

		Emulator_DestroyTextures();

		Emulator_DestroyGlobalShaders();

		if (recreate)
		{
			Emulator_CreateGlobalShaders();

			Emulator_GenerateCommonTextures();

			Emulator_CreateVertexBuffer();

			Emulator_CreateIndexBuffer();
		}

		g_resettingDevice = FALSE;
	}
}

void Emulator_DestroyTextures()
{
	glBindTexture(1, 0);

	glDeleteTextures(1, &vramTexture);
	glDeleteTextures(1, &rg8lutTexture);
	glDeleteTextures(1, &whiteTexture);

	vramTexture = 0;
	rg8lutTexture = 0;
	whiteTexture = 0;
}

void Emulator_DestroyGlobalShaders()
{
	glUseProgram(0);

	glDeleteProgram(g_gte_shader_4.program);
	glDeleteProgram(g_gte_shader_8.program);
	glDeleteProgram(g_gte_shader_16.program);
	glDeleteProgram(g_blit_shader.program);

	g_gte_shader_4.program = 0;
	g_gte_shader_8.program = 0;
	g_gte_shader_16.program = 0;
	g_blit_shader.program = 0;
}

int Emulator_InitialiseGLExtensions()
{
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
	if (glGetShaderInfoLog == NULL)
	{
		return FALSE;
	}

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
	if (glGetProgramInfoLog == NULL)
	{
		return FALSE;
	}

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
	if (glCreateProgram == NULL)
	{
		return FALSE;
	}

	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
	if (glCreateShader == NULL)
	{
		return FALSE;
	}

	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
	if (glShaderSource == NULL)
	{
		return FALSE;
	}

	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
	if (glCompileShader == NULL)
	{
		return FALSE;
	}

	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
	if (glAttachShader == NULL)
	{
		return FALSE;
	}

	glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
	if (glDeleteShader == NULL)
	{
		return FALSE;
	}

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glBindAttribLocation");
	if (glBindAttribLocation == NULL)
	{
		return FALSE;
	}

	glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
	if (glLinkProgram == NULL)
	{
		return FALSE;
	}

	glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
	if (glUseProgram == NULL)
	{
		return FALSE;
	}

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)SDL_GL_GetProcAddress("glGetUniformLocation");
	if (glGetUniformLocation == NULL)
	{
		return FALSE;
	}

	glUniform1i = (PFNGLUNIFORM1IPROC)SDL_GL_GetProcAddress("glUniform1i");
	if (glUniform1i == NULL)
	{
		return FALSE;
	}

	glDeleteBuffers = (PFNGLDELETEBUFFERSARBPROC)SDL_GL_GetProcAddress("glDeleteBuffers");
	if (glDeleteBuffers == NULL)
	{
		return FALSE;
	}

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glDeleteVertexArrays");
	if (glDeleteVertexArrays == NULL)
	{
		return FALSE;
	}

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
	if (glDeleteProgram == NULL)
	{
		return FALSE;
	}

	glGenBuffers = (PFNGLGENBUFFERSARBPROC)SDL_GL_GetProcAddress("glGenBuffers");
	if (glGenBuffers == NULL)
	{
		return FALSE;
	}

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glGenVertexArrays");
	if (glGenVertexArrays == NULL)
	{
		return FALSE;
	}

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)SDL_GL_GetProcAddress("glBindVertexArray");
	if (glBindVertexArray == NULL)
	{
		return FALSE;
	}

	glBindBuffer = (PFNGLBINDBUFFERARBPROC)SDL_GL_GetProcAddress("glBindBuffer");
	if (glBindBuffer == NULL)
	{
		return FALSE;
	}

	glBufferData = (PFNGLBUFFERDATAARBPROC)SDL_GL_GetProcAddress("glBufferData");
	if (glBufferData == NULL)
	{
		return FALSE;
	}

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
	if (glEnableVertexAttribArray == NULL)
	{
		return FALSE;
	}

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)SDL_GL_GetProcAddress("glVertexAttribPointer");
	if (glVertexAttribPointer == NULL)
	{
		return FALSE;
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)SDL_GL_GetProcAddress("glUniformMatrix4fv");
	if (glUniformMatrix4fv == NULL)
	{
		return FALSE;
	}

	glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)SDL_GL_GetProcAddress("glDrawElementsBaseVertex");
	if (glDrawElementsBaseVertex == NULL)
	{
		return FALSE;
	}

	glBufferSubData = (PFNGLBUFFERSUBDATAARBPROC)SDL_GL_GetProcAddress("glBufferSubData");
	if (glBufferSubData == NULL)
	{
		return FALSE;
	}

	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)SDL_GL_GetProcAddress("glBindFramebuffer");
	if (glBindFramebuffer == NULL)
	{
		return FALSE;
	}

	glActiveTextureARB2 = (PFNGLACTIVETEXTUREARBPROC)SDL_GL_GetProcAddress("glActiveTextureARB");
	if (glActiveTextureARB2 == NULL)
	{
		return FALSE;
	}

	glBlendColorEXT = (PFNGLBLENDCOLOREXTPROC)SDL_GL_GetProcAddress("glBlendColorEXT");
	if (glBlendColorEXT == NULL)
	{
		return FALSE;
	}

	glBlendEquationEXT = (PFNGLBLENDEQUATIONEXTPROC)SDL_GL_GetProcAddress("glBlendEquationEXT");
	if (glBlendEquationEXT == NULL)
	{
		return FALSE;
	}

	return TRUE;
}

int Emulator_InitialiseGLContext(char* windowName)
{
#if defined(SDL2)
#if defined(_WINDOWS) && defined(EDITOR)

	if (g_overrideHWND != NULL)
	{
		SDL_SetHint(SDL_HINT_VIDEO_FOREIGN_WINDOW_OPENGL, "1");
		g_window = SDL_CreateWindowFrom(g_overrideHWND);
		SDL_GL_MakeCurrent(g_window, SDL_GL_CreateContext(g_window));
		SDL_SetWindowSize(g_window, Emulator_GetWindowWidth(), Emulator_GetWindowHeight());
	}
	else
	{
		eassert(FALSE);//?
	}
#else
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	SDL_GL_CreateContext(g_window);
#endif
#endif


#if defined(SDL2)
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window or GL context!\n");
		return FALSE;
	}
#endif

	if (Emulator_InitialiseGLExtensions() == FALSE)
	{
		eprinterr("Failed to initialise OpenGL extensions!\n");
		return FALSE;
	}

	return TRUE;
}

void Emulator_CreateGlobalShaders()
{
	g_gte_shader_4 = Shader_Compile(gte_shader_4);
	g_gte_shader_8 = Shader_Compile(gte_shader_8);
	g_gte_shader_16 = Shader_Compile(gte_shader_16);
	g_blit_shader = Shader_Compile(blit_shader);
}

unsigned char pixelData[64 * 64 * sizeof(unsigned int)];

void Emulator_GenerateCommonTextures()
{
	memset(pixelData, 0xFF, sizeof(pixelData));
	
	glGenTextures(1, &whiteTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, whiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	glGenTextures(1, &rg8lutTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, rg8lutTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LUT_WIDTH, LUT_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, Emulator_GenerateRG8LUT());
	
	glGenTextures(1, &vramTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, VRAM_INTERNAL_FORMAT, VRAM_WIDTH, VRAM_HEIGHT, 0, VRAM_FORMAT, GL_UNSIGNED_BYTE, vram);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Emulator_CreateVertexBuffer()
{
	glGenBuffers(1, &dynamic_vertex_buffer);
	glGenVertexArrays(1, &dynamic_vertex_array);
	glBindVertexArray(dynamic_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, dynamic_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);

	glEnableVertexAttribArray(a_color);
#if defined(PGXP)
	glVertexAttribPointer(a_position, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->x);
#else
	glVertexAttribPointer(a_position, 4, GL_SHORT, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->x);
#endif
	glVertexAttribPointer(a_texcoord, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->u);
	glVertexAttribPointer(a_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), &((Vertex*)NULL)->r);
#if defined(PGXP)
	glVertexAttribPointer(a_z, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->z);
	glVertexAttribPointer(a_w, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->w);

	glEnableVertexAttribArray(a_z);
	glEnableVertexAttribArray(a_w);
#endif
}

void Emulator_CreateIndexBuffer()
{
	glGenBuffers(1, &dynamic_index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dynamic_index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * MAX_NUM_INDEX_BUFFER_INDICES, NULL, GL_DYNAMIC_DRAW);
}

int Emulator_CreateCommonResources()
{
	memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

	Emulator_GenerateCommonTextures();

	Emulator_CreateGlobalShaders();

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glBlendColor(0.5f, 0.5f, 0.5f, 0.25f);

	Emulator_CreateVertexBuffer();

	Emulator_CreateIndexBuffer();

	//Emulator_ResetDevice();

	return TRUE;
}

void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
{
	float a = 2.0f / (right - left);
	float b = 2.0f / (top - bottom);
	float c = 2.0f / (znear - zfar);

	float x = (left + right) / (left - right);
	float y = (bottom + top) / (bottom - top);
	float z = (znear + zfar) / (znear - zfar);

	float ortho[16] = {
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		x, y, z, 1
	};

	glUniformMatrix4fv(u_Projection, 1, GL_FALSE, ortho);
}

void Emulator_SetShader(const ShaderID shader)
{
	glUseProgram(shader.program);

	u_Projection = glGetUniformLocation(shader.program, "Projection");

	Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0.0f, 0.0f, 1.0f);
}

void Emulator_SetTextureAndShader(TextureID texture, ShaderID shader)
{
	Emulator_SetShader(shader);

	if (g_texturelessMode) {
		texture = whiteTexture;
	}

	if (g_lastBoundTexture[0] == texture && g_lastBoundTexture[1] == rg8lutTexture) {
		//return;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, rg8lutTexture);

	g_lastBoundTexture[0] = texture;
	g_lastBoundTexture[1] = rg8lutTexture;
}

void Emulator_DestroyTexture(TextureID texture)
{
	glDeleteTextures(1, &texture);
}

void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

#define NOFILE 0

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)

void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif
	FILE* f = fopen(outputFileName, "wb");

	if (f == NULL)
	{
		return;
	}

	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6];
	header[0] = (width % 256);
	header[1] = (width / 256);
	header[2] = (height % 256);
	header[3] = (height / 256);
	header[4] = 16;
	header[5] = 0;

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);

	//512 const is hdd sector size
	int numSectorsToWrite = (width * height * sizeof(unsigned short)) / 512;
	int numRemainingSectorsToWrite = (width * height * sizeof(unsigned short)) % 512;

	for (int i = 0; i < numSectorsToWrite; i++)
	{
		fwrite(&vram[i * 512 / sizeof(unsigned short)], 512, 1, f);
	}

	for (int i = 0; i < numRemainingSectorsToWrite; i++)
	{
		fwrite(&vram[numSectorsToWrite * 512 / sizeof(unsigned short)], numRemainingSectorsToWrite, 1, f);
	}

	fclose(f);
}
#endif

void Emulator_StoreFrameBuffer(int x, int y, int w, int h)
{
	short* fb = (short*)malloc(w * h * sizeof(short));

	int* data = (int*)malloc(w * h * sizeof(int));
	glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);

#define FLIP_Y (h - fy - 1)
#define SWAP_RB

	unsigned int* data_src = (unsigned int*)data;
	unsigned short* data_dst = (unsigned short*)fb;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			unsigned int  c = *data_src++;
			unsigned char b = ((c >> 3) & 0x1F);
			unsigned char g = ((c >> 11) & 0x1F);
			unsigned char r = ((c >> 19) & 0x1F);
#if defined(SWAP_RB)
			*data_dst++ = b | (g << 5) | (r << 10) | 0x8000;
#else
			* data_dst++ = r | (g << 5) | (b << 10) | 0x8000;
#endif
		}
	}

	short* ptr = (short*)vram + VRAM_WIDTH * y + x;

	for (int fy = 0; fy < h; fy++) {
		short* fb_ptr = fb + (h * FLIP_Y / h) * w;

		for (int fx = 0; fx < w; fx++) {
			ptr[fx] = fb_ptr[w * fx / w];
		}

		ptr += VRAM_WIDTH;
	}

	free(data);

#undef FLIP_Y

	free(fb);

	vram_need_update = TRUE;
}

void Emulator_UpdateVRAM()
{
	if (!vram_need_update) {
		return;
	}
	vram_need_update = FALSE;

	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, VRAM_WIDTH, VRAM_HEIGHT, VRAM_FORMAT, GL_UNSIGNED_BYTE, vram);
}

void Emulator_SetWireframe(int enable)
{
	glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
}

void Emulator_SetBlendMode(BlendMode blendMode)
{
	if (g_PreviousBlendMode == blendMode)
	{
		return;
	}

	if (g_PreviousBlendMode == BM_NONE)
	{
		glEnable(GL_BLEND);
	}

	switch (blendMode)
	{
	case BM_NONE:
		glDisable(GL_BLEND);
		break;
	case BM_AVERAGE:
		glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_COLOR);
		glBlendEquation(GL_FUNC_ADD);
		break;
	case BM_ADD:
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		break;
	case BM_SUBTRACT:
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
		break;
	case BM_ADD_QUATER_SOURCE:
		glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		break;
	}

	g_PreviousBlendMode = blendMode;
}

void Emulator_DrawTriangles(int start_vertex, int start_index, int triangles)
{
	if (triangles <= 0)
		return;

	glDrawElements(GL_TRIANGLES, triangles * 3, GL_UNSIGNED_SHORT, (void*)(sizeof(unsigned short)*start_index));
}

void Emulator_UpdateVertexBuffer(const struct Vertex* vertices, int num_vertices, int vertex_start_index, int use_offset)
{
	eassert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);

	if (num_vertices <= 0)
		return;

	if (use_offset)
	{
		vertices += vertex_start_index;
	}

	glBufferSubData(GL_ARRAY_BUFFER, vertex_start_index * sizeof(Vertex), num_vertices * sizeof(Vertex), vertices);

	vbo_was_dirty_flag = TRUE;
}

void Emulator_UpdateIndexBuffer(const unsigned short* indices, int num_indices, int face_start_index, int use_offset)
{
	eassert(num_indices <= MAX_NUM_INDEX_BUFFER_INDICES);

	if (num_indices <= 0)
		return;

	if (use_offset)
	{
		indices += face_start_index;
	}

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, face_start_index * sizeof(unsigned short), num_indices * sizeof(unsigned short), indices);
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
	int offset_x = activeDispEnv.screen.x;
	int offset_y = activeDispEnv.screen.y;

	glViewport(x + offset_x, y + -offset_y, width, height);
}

void Emulator_SwapWindow()
{
	unsigned int timer = 1;

#if defined(SINGLE_THREADED_AUDIO)
	Emulator_CounterWrapper(0, &timer);
#endif

	Emulator_WaitForTimestep(1);

	SDL_GL_SwapWindow(g_window);
}

void Emulator_WaitForTimestep(int count)
{
	if (g_swapInterval > 0)
	{
		int64_t delta = g_swapTime + FIXED_TIME_STEP * count - Emulator_GetTicks();

		if (delta > 0) {
			SDL_Delay((unsigned int)delta);
		}
	}

	g_swapTime = Emulator_GetTicks();
}

void Emulator_SetRenderTarget(const RenderTargetID& frameBufferObject)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
}

#endif
