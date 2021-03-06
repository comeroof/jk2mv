// tr_init.c -- functions that are not called every frame

#include "tr_local.h"

#ifndef DEDICATED
#if !defined __TR_WORLDEFFECTS_H
	#include "tr_WorldEffects.h"
#endif
#endif //!DEDICATED

#include "tr_font.h"

#ifdef G2_COLLISION_ENABLED
#if !defined (MINIHEAP_H_INC)
	#include "../qcommon/MiniHeap.h"
#endif

#include "../ghoul2/G2_local.h"
#endif


//#ifdef __USEA3D
//// Defined in snd_a3dg_refcommon.c
//void RE_A3D_RenderGeometry (void *pVoidA3D, void *pVoidGeom, void *pVoidMat, void *pVoidGeomStatus);
//#endif

#ifdef G2_COLLISION_ENABLED
CMiniHeap *G2VertSpaceServer = NULL;
#endif

#ifndef DEDICATED
glconfig_t	glConfig;
glstate_t	glState;
static void GfxInfo_f( void );

#endif


cvar_t	*r_flareSize;
cvar_t	*r_flareFade;

cvar_t	*r_ignoreFastPath;

cvar_t	*r_verbose;
cvar_t	*r_ignore;

cvar_t	*r_displayRefresh;

cvar_t	*r_detailTextures;

cvar_t	*r_znear;

cvar_t	*r_smp;
cvar_t	*r_showSmp;
cvar_t	*r_skipBackEnd;

cvar_t	*r_measureOverdraw;

cvar_t	*r_inGameVideo;
cvar_t	*r_fastsky;
cvar_t	*r_drawSun;
cvar_t	*r_dynamiclight;
cvar_t	*r_dlightBacks;

cvar_t	*r_lodbias;
cvar_t	*r_lodscale;
cvar_t	*r_autolodscalevalue;

cvar_t	*r_newDLights;

cvar_t	*r_norefresh;
cvar_t	*r_drawentities;
cvar_t	*r_drawworld;
cvar_t	*r_speeds;
cvar_t	*r_fullbright;
cvar_t	*r_novis;
cvar_t	*r_nocull;
cvar_t	*r_facePlaneCull;
cvar_t	*r_showcluster;
cvar_t	*r_nocurves;

cvar_t	*r_surfaceSprites;
cvar_t	*r_surfaceWeather;

cvar_t	*r_windSpeed;
cvar_t	*r_windAngle;
cvar_t	*r_windGust;
cvar_t	*r_windDampFactor;
cvar_t	*r_windPointForce;
cvar_t	*r_windPointX;
cvar_t	*r_windPointY;

cvar_t	*r_allowExtensions;

cvar_t	*r_ext_compressed_textures;
cvar_t	*r_ext_compressed_lightmaps;
cvar_t	*r_ext_preferred_tc_method;
cvar_t	*r_ext_gamma_control;
cvar_t	*r_ext_multitexture;
cvar_t	*r_ext_compiled_vertex_array;
cvar_t	*r_ext_texture_env_add;
cvar_t	*r_ext_texture_filter_anisotropic;

#ifdef JKA_DYNAMIC_GLOW
cvar_t	*r_DynamicGlow;
cvar_t	*r_DynamicGlowPasses;
cvar_t	*r_DynamicGlowDelta;
cvar_t	*r_DynamicGlowIntensity;
cvar_t	*r_DynamicGlowSoft;
cvar_t	*r_DynamicGlowWidth;
cvar_t	*r_DynamicGlowHeight;
#endif

cvar_t	*r_ignoreGLErrors;
cvar_t	*r_logFile;

cvar_t	*r_stencilbits;
cvar_t	*r_depthbits;
cvar_t	*r_colorbits;
cvar_t	*r_stereo;
cvar_t	*r_primitives;
cvar_t	*r_texturebits;
cvar_t	*r_texturebitslm;

cvar_t	*r_drawBuffer;
cvar_t	*r_lightmap;
cvar_t	*r_vertexLight;
cvar_t	*r_uiFullScreen;
cvar_t	*r_shadows;
cvar_t	*r_flares;
cvar_t	*r_mode;
cvar_t	*r_aspectratio;
cvar_t	*r_nobind;
cvar_t	*r_singleShader;
cvar_t	*r_colorMipLevels;
cvar_t	*r_picmip;
cvar_t	*r_showtris;
cvar_t	*r_showsky;
cvar_t	*r_shownormals;
cvar_t	*r_finish;
cvar_t	*r_clear;
cvar_t	*r_swapInterval;
cvar_t	*r_textureMode;
cvar_t	*r_offsetFactor;
cvar_t	*r_offsetUnits;
cvar_t	*r_gamma;
cvar_t	*r_intensity;
cvar_t	*r_lockpvs;
cvar_t	*r_noportals;
cvar_t	*r_portalOnly;

cvar_t	*r_subdivisions;
cvar_t	*r_lodCurveError;

cvar_t	*r_fullscreen;

cvar_t	*r_customwidth;
cvar_t	*r_customheight;
cvar_t	*r_customaspect;

cvar_t	*r_overBrightBits;

cvar_t	*r_debugSurface;
cvar_t	*r_simpleMipMaps;

cvar_t	*r_showImages;

cvar_t	*r_ambientScale;
cvar_t	*r_directedScale;
cvar_t	*r_debugLight;
cvar_t	*r_debugSort;
cvar_t	*r_printShaders;

cvar_t	*r_maxpolys;
int		max_polys;
cvar_t	*r_maxpolyverts;
int		max_polyverts;

cvar_t	*r_modelpoolmegs;
cvar_t *r_screenshotJpegQuality;

// ouned: gamma correction
cvar_t *r_gammamethod;

/*
Ghoul2 Insert Start
*/

cvar_t	*r_noServerGhoul2;
cvar_t	*r_Ghoul2AnimSmooth=0;
cvar_t	*r_Ghoul2UnSqashAfterSmooth=0;
//cvar_t	*r_Ghoul2UnSqash;
//cvar_t	*r_Ghoul2TimeBase=0; from single player
//cvar_t	*r_Ghoul2NoLerp;
//cvar_t	*r_Ghoul2NoBlend;
//cvar_t	*r_Ghoul2BlendMultiplier=0;

/*
Ghoul2 Insert End
*/

#ifndef DEDICATED
#ifdef WIN32
void ( APIENTRY * qglMultiTexCoord2fARB )( GLenum texture, GLfloat s, GLfloat t );
void ( APIENTRY * qglActiveTextureARB )( GLenum texture );
void ( APIENTRY * qglClientActiveTextureARB )( GLenum texture );

void ( APIENTRY * qglLockArraysEXT)( GLint, GLint);
void ( APIENTRY * qglUnlockArraysEXT) ( void );

void ( APIENTRY * qglPointParameterfEXT)( GLenum, GLfloat);
void ( APIENTRY * qglPointParameterfvEXT)( GLenum, GLfloat *);

#ifdef JKA_DYNAMIC_GLOW// GLOWXXX
// Declare Register Combiners function pointers.
PFNGLCOMBINERPARAMETERFVNV				qglCombinerParameterfvNV = NULL;
PFNGLCOMBINERPARAMETERIVNV				qglCombinerParameterivNV = NULL;
PFNGLCOMBINERPARAMETERFNV				qglCombinerParameterfNV = NULL;
PFNGLCOMBINERPARAMETERINV				qglCombinerParameteriNV = NULL;
PFNGLCOMBINERINPUTNV					qglCombinerInputNV = NULL;
PFNGLCOMBINEROUTPUTNV					qglCombinerOutputNV = NULL;
PFNGLFINALCOMBINERINPUTNV				qglFinalCombinerInputNV = NULL;
PFNGLGETCOMBINERINPUTPARAMETERFVNV		qglGetCombinerInputParameterfvNV = NULL;
PFNGLGETCOMBINERINPUTPARAMETERIVNV		qglGetCombinerInputParameterivNV = NULL;
PFNGLGETCOMBINEROUTPUTPARAMETERFVNV		qglGetCombinerOutputParameterfvNV = NULL;
PFNGLGETCOMBINEROUTPUTPARAMETERIVNV		qglGetCombinerOutputParameterivNV = NULL;
PFNGLGETFINALCOMBINERINPUTPARAMETERFVNV	qglGetFinalCombinerInputParameterfvNV = NULL;
PFNGLGETFINALCOMBINERINPUTPARAMETERIVNV	qglGetFinalCombinerInputParameterivNV = NULL;

// Declare Pixel Format function pointers.
PFNWGLGETPIXELFORMATATTRIBIVARBPROC		qwglGetPixelFormatAttribivARB = NULL;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC		qwglGetPixelFormatAttribfvARB = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC			qwglChoosePixelFormatARB = NULL;

// Declare Pixel Buffer function pointers.
PFNWGLCREATEPBUFFERARBPROC				qwglCreatePbufferARB = NULL;
PFNWGLGETPBUFFERDCARBPROC				qwglGetPbufferDCARB = NULL;
PFNWGLRELEASEPBUFFERDCARBPROC			qwglReleasePbufferDCARB = NULL;
PFNWGLDESTROYPBUFFERARBPROC				qwglDestroyPbufferARB = NULL;
PFNWGLQUERYPBUFFERARBPROC				qwglQueryPbufferARB = NULL;

// Declare Render-Texture function pointers.
PFNWGLBINDTEXIMAGEARBPROC				qwglBindTexImageARB = NULL;
PFNWGLRELEASETEXIMAGEARBPROC			qwglReleaseTexImageARB = NULL;
PFNWGLSETPBUFFERATTRIBARBPROC			qwglSetPbufferAttribARB = NULL;

// Declare Vertex and Fragment Program function pointers.
PFNGLPROGRAMSTRINGARBPROC qglProgramStringARB = NULL;
PFNGLBINDPROGRAMARBPROC qglBindProgramARB = NULL;
PFNGLDELETEPROGRAMSARBPROC qglDeleteProgramsARB = NULL;
PFNGLGENPROGRAMSARBPROC qglGenProgramsARB = NULL;
PFNGLPROGRAMENVPARAMETER4DARBPROC qglProgramEnvParameter4dARB = NULL;
PFNGLPROGRAMENVPARAMETER4DVARBPROC qglProgramEnvParameter4dvARB = NULL;
PFNGLPROGRAMENVPARAMETER4FARBPROC qglProgramEnvParameter4fARB = NULL;
PFNGLPROGRAMENVPARAMETER4FVARBPROC qglProgramEnvParameter4fvARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4DARBPROC qglProgramLocalParameter4dARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4DVARBPROC qglProgramLocalParameter4dvARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FARBPROC qglProgramLocalParameter4fARB = NULL;
PFNGLPROGRAMLOCALPARAMETER4FVARBPROC qglProgramLocalParameter4fvARB = NULL;
PFNGLGETPROGRAMENVPARAMETERDVARBPROC qglGetProgramEnvParameterdvARB = NULL;
PFNGLGETPROGRAMENVPARAMETERFVARBPROC qglGetProgramEnvParameterfvARB = NULL;
PFNGLGETPROGRAMLOCALPARAMETERDVARBPROC qglGetProgramLocalParameterdvARB = NULL;
PFNGLGETPROGRAMLOCALPARAMETERFVARBPROC qglGetProgramLocalParameterfvARB = NULL;
PFNGLGETPROGRAMIVARBPROC qglGetProgramivARB = NULL;
PFNGLGETPROGRAMSTRINGARBPROC qglGetProgramStringARB = NULL;
PFNGLISPROGRAMARBPROC qglIsProgramARB = NULL;
#endif

// ouned: gamma correction
PFNGLGETHANDLEARBPROC qglGetHandleARB = NULL;
PFNGLDELETEOBJECTARBPROC qglDeleteObjectARB = NULL;
PFNGLDETACHOBJECTARBPROC qglDetachObjectARB = NULL;
PFNGLCREATESHADEROBJECTARBPROC qglCreateShaderObjectARB = NULL;
PFNGLSHADERSOURCEARBPROC qglShaderSourceARB = NULL;
PFNGLCOMPILESHADERARBPROC qglCompileShaderARB = NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC qglCreateProgramObjectARB = NULL;
PFNGLATTACHOBJECTARBPROC qglAttachObjectARB = NULL;
PFNGLLINKPROGRAMARBPROC	qglLinkProgramARB = NULL;
PFNGLUSEPROGRAMOBJECTARBPROC qglUseProgramObjectARB = NULL;
PFNGLVALIDATEPROGRAMARBPROC	qglValidateProgramARB = NULL;
PFNGLGETUNIFORMLOCATIONARBPROC qglGetUniformLocationARB = NULL;
PFNGLUNIFORM1IARBPROC qglUniform1iARB = NULL;
PFNGLUNIFORM1FARBPROC qglUniform1fARB = NULL;
PFNGLUNIFORM4FARBPROC qglUniform4fARB = NULL;
PFNGLUNIFORM4FVARBPROC qglUniform4fvARB = NULL;
PFNGLGETINFOLOGARBPROC qglGetInfoLogARB = NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC qglGetObjectParameterivARB = NULL;
PFNGLGETATTACHEDOBJECTSARBPROC qglGetAttachedObjectsARB = NULL;

GLboolean(APIENTRY * qglIsRenderbufferEXT) (GLuint renderbuffer);
void			(APIENTRY * qglBindRenderbufferEXT) (GLenum target, GLuint renderbuffer);
void			(APIENTRY * qglDeleteRenderbuffersEXT) (GLsizei n, const GLuint * renderbuffers);
void			(APIENTRY * qglGenRenderbuffersEXT) (GLsizei n, GLuint * renderbuffers);
void			(APIENTRY * qglRenderbufferStorageEXT) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
void			(APIENTRY * qglGetRenderbufferParameterivEXT) (GLenum target, GLenum pname, GLint * params);
GLboolean(APIENTRY * qglIsFramebufferEXT) (GLuint framebuffer);
void			(APIENTRY * qglBindFramebufferEXT) (GLenum target, GLuint framebuffer);
void			(APIENTRY * qglDeleteFramebuffersEXT) (GLsizei n, const GLuint * framebuffers);
void			(APIENTRY * qglGenFramebuffersEXT) (GLsizei n, GLuint * framebuffers);
GLenum(APIENTRY * qglCheckFramebufferStatusEXT) (GLenum target);
void			(APIENTRY * qglFramebufferTexture1DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void			(APIENTRY * qglFramebufferTexture2DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void			(APIENTRY * qglFramebufferTexture3DEXT) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
void			(APIENTRY * qglFramebufferRenderbufferEXT) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void			(APIENTRY * qglGetFramebufferAttachmentParameterivEXT) (GLenum target, GLenum attachment, GLenum pname, GLint * params);
void			(APIENTRY * qglGenerateMipmapEXT) (GLenum target);
void			(APIENTRY * qglBlitFramebufferEXT) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

#endif

void RE_SetLightStyle(int style, int color);

void RE_GetBModelVerts( int bmodelIndex, vec3_t *verts, vec3_t normal );

#endif // !DEDICATED

static void AssertCvarRange( cvar_t *cv, float minVal, float maxVal, qboolean shouldBeIntegral )
{
	if ( shouldBeIntegral )
	{
		if ( ( int ) cv->value != cv->integer )
		{
			ri.Printf( PRINT_WARNING, "WARNING: cvar '%s' must be integral (%f)\n", cv->name, cv->value );
			ri.Cvar_Set( cv->name, va( "%d", cv->integer ) );
		}
	}

	if ( cv->value < minVal )
	{
		ri.Printf( PRINT_WARNING, "WARNING: cvar '%s' out of range (%f < %f)\n", cv->name, cv->value, minVal );
		ri.Cvar_Set( cv->name, va( "%f", minVal ) );
	}
	else if ( cv->value > maxVal )
	{
		ri.Printf( PRINT_WARNING, "WARNING: cvar '%s' out of range (%f > %f)\n", cv->name, cv->value, maxVal );
		ri.Cvar_Set( cv->name, va( "%f", maxVal ) );
	}
}

#ifndef DEDICATED

/*
** InitOpenGL
**
** This function is responsible for initializing a valid OpenGL subsystem.  This
** is done by calling GLimp_Init (which gives us a working OGL subsystem) then
** setting variables, checking GL constants, and reporting the gfx system config
** to the user.
*/
static void InitOpenGL( void )
{
	//
	// initialize OS specific portions of the renderer
	//
	// GLimp_Init directly or indirectly references the following cvars:
	//		- r_fullscreen
	//		- r_mode
	//		- r_(color|depth|stencil)bits
	//		- r_gamma
	//

	if ( glConfig.vidWidth == 0 )
	{
		GLimp_Init();
		// print info the first time only
		GfxInfo_f();
	}

	// init command buffers and SMP
	R_InitCommandBuffers();

	// set default state
	GL_SetDefaultState();
}

/*
==================
GL_CheckErrors
==================
*/
void GL_CheckErrors( void ) {
	int		err;
	char	s[64];

	err = qglGetError();
	if ( err == GL_NO_ERROR ) {
		return;
	}
	if ( r_ignoreGLErrors->integer ) {
		return;
	}
	switch( err ) {
		case GL_INVALID_ENUM:
			strcpy( s, "GL_INVALID_ENUM" );
			break;
		case GL_INVALID_VALUE:
			strcpy( s, "GL_INVALID_VALUE" );
			break;
		case GL_INVALID_OPERATION:
			strcpy( s, "GL_INVALID_OPERATION" );
			break;
		case GL_STACK_OVERFLOW:
			strcpy( s, "GL_STACK_OVERFLOW" );
			break;
		case GL_STACK_UNDERFLOW:
			strcpy( s, "GL_STACK_UNDERFLOW" );
			break;
		case GL_OUT_OF_MEMORY:
			strcpy( s, "GL_OUT_OF_MEMORY" );
			break;
		default:
			Com_sprintf( s, sizeof(s), "%i", err);
			break;
	}

	ri.Error( ERR_FATAL, "GL_CheckErrors: %s", s );
}

#endif //!DEDICATED

/*
** R_GetModeInfo
*/
typedef struct vidmode_s
{
	const char *description;
	int		 width, height;
	float		pixelAspect;		// pixel width / height
} vidmode_t;

// ouned: screen resolutions
vidmode_t r_vidModes[] = {
	// 4:3
	{ "Mode  0:  320x240",	320,  240,  1 },
	{ "Mode  1:  400x300",	400,  300,  1 },
	{ "Mode  2:  512x384",	512,  384,  1 },
	{ "Mode  3:  640x480",	640,  480,  1 },
	{ "Mode  4:  800x600",	800,  600,  1 },
	{ "Mode  5:  960x720",	960,  720,  1 },
	{ "Mode  6:  1024x768",   1024, 768,  1 },
	{ "Mode  7:  1152x864",   1152, 864,  1 },
	{ "Mode  8:  1280x1024",  1280, 1024, 1 },
	{ "Mode  9:  1600x1200",  1600, 1200, 1 },
	{ "Mode  10: 2048x1536",  2048, 1536, 1 },

	// 16:9
	{ "Mode  11: 960x540",	960,  540,  1 },
	{ "Mode  12: 960x544",	960,  544,  1 },
	{ "Mode  13: 1024x576",   1024, 576,  1 },
	{ "Mode  14: 1024x600",   1024, 600,  1 },
	{ "Mode  15: 1136x640",   1136, 640,  1 },
	{ "Mode  16: 1280x720",   1280, 720,  1 },
	{ "Mode  17: 1366x768",   1366, 768,  1 },
	{ "Mode  18: 1600x900",   1600, 900,  1 },
	{ "Mode  19: 1920x1080",  1920, 1080, 1 },
	{ "Mode  20: 2048x1152",  2048, 1152, 1 },
	{ "Mode  21: 2560x1440",  2560, 1400, 1 },
	{ "Mode  22: 2880x1620",  2880, 1620, 1 },
	{ "Mode  23: 3200x1800",  3200, 1800, 1 },
	{ "Mode  24: 3840x2160",  3840, 2160, 1 },
	{ "Mode  25: 4096x2304",  4096, 2304, 1 },
	{ "Mode  26: 5120x2880",  5120, 2880, 1 },

	// 16:10
	{ "Mode  27: 1280x800",   1280, 800,  1 },
	{ "Mode  28: 1440x900",   1440, 900,  1 },
	{ "Mode  29: 1680x1050",  1680, 1050, 1 },
	{ "Mode  30: 1920x1200",  1920, 1200, 1 },
	{ "Mode  31: 2560x1600",  2560, 1600, 1 },
};
static int	s_numVidModes = ( sizeof( r_vidModes ) / sizeof( r_vidModes[0] ) );

qboolean R_GetModeInfo( int *width, int *height, float *windowAspect, int mode ) {
	vidmode_t	*vm;

	if ( mode < -2 ) {
		return qfalse;
	}
	if ( mode >= s_numVidModes ) {
		return qfalse;
	}

	if ( mode == -1 ) {
		*width = r_customwidth->integer;
		*height = r_customheight->integer;
		*windowAspect = r_customaspect->value;
		return qtrue;
	}

	// ouned: native resolution
	if (mode == -2) {
		return qtrue;
	}

	vm = &r_vidModes[mode];

	*width  = vm->width;
	*height = vm->height;
	*windowAspect = (float)vm->width / ( vm->height * vm->pixelAspect );

	return qtrue;
}

/*
** R_ModeList_f
*/
static void R_ModeList_f( void )
{
	int i;

	ri.Printf( PRINT_ALL, "\n" );
	for ( i = 0; i < s_numVidModes; i++ )
	{
		ri.Printf( PRINT_ALL, "%s\n", r_vidModes[i].description );
	}
	ri.Printf( PRINT_ALL, "\n" );
}


/*
==============================================================================

						SCREEN SHOTS

==============================================================================
*/
#ifndef DEDICATED
/*
==================
R_TakeScreenshot
==================
*/

byte *RB_ReadPixels(int x, int y, int width, int height, size_t *offset, int *padlen)
{
	byte *buffer, *bufstart;
	int padwidth, linelen;
	GLint packAlign;

	qglGetIntegerv(GL_PACK_ALIGNMENT, &packAlign);

	linelen = width * 3;
	padwidth = PAD(linelen, packAlign);

	// Allocate a few more bytes so that we can choose an alignment we like
	buffer = (byte *)Hunk_AllocateTempMemory((int)(padwidth * height + *offset + packAlign - 1));

	bufstart = (byte *)PADP((intptr_t)buffer + *offset, packAlign);
	qglReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, bufstart);

	*offset = bufstart - buffer;
	*padlen = padwidth - linelen;

	return buffer;
}

void R_TakeScreenshot(int x, int y, int width, int height, char *fileName) {
	byte *allbuf, *buffer;
	byte *srcptr, *destptr;
	byte *endline, *endmem;
	byte temp;

	int linelen, padlen;
	size_t offset = 18, memcount;

	allbuf = RB_ReadPixels(x, y, width, height, &offset, &padlen);
	buffer = allbuf + offset - 18;

	Com_Memset(buffer, 0, 18);
	buffer[2] = 2;		// uncompressed type
	buffer[12] = width & 255;
	buffer[13] = width >> 8;
	buffer[14] = height & 255;
	buffer[15] = height >> 8;
	buffer[16] = 24;	// pixel size

	// swap rgb to bgr and remove padding from line endings
	linelen = width * 3;

	srcptr = destptr = allbuf + offset;
	endmem = srcptr + (linelen + padlen) * height;

	while (srcptr < endmem)
	{
		endline = srcptr + linelen;

		while (srcptr < endline)
		{
			temp = srcptr[0];
			*destptr++ = srcptr[2];
			*destptr++ = srcptr[1];
			*destptr++ = temp;

			srcptr += 3;
		}

		// Skip the pad
		srcptr += padlen;
	}

	memcount = linelen * height;

	// gamma correct
	if (glConfig.deviceSupportsGamma)
		R_GammaCorrect(allbuf + offset, (int)memcount);

	ri.FS_WriteFile(fileName, buffer, (int)memcount + 18);

	ri.Hunk_FreeTempMemory(allbuf);
}

void R_TakeScreenshotJPEG(int x, int y, int width, int height, char *fileName) {
	byte *buffer;
	size_t offset = 0, memcount;
	int padlen;

	buffer = RB_ReadPixels(x, y, width, height, &offset, &padlen);
	memcount = (width * 3 + padlen) * height;

	// gamma correct
	if (glConfig.deviceSupportsGamma)
		R_GammaCorrect(buffer + offset, (int)memcount);

	SaveJPG(fileName, r_screenshotJpegQuality->integer, width, height, buffer + offset, padlen);
	ri.Hunk_FreeTempMemory(buffer);
}

/*
==================
R_ScreenshotFilename
==================
*/
void R_ScreenshotFilename( int lastNumber, char *fileName, const char *psExt ) {
	int		a,b,c,d;

	if ( lastNumber < 0 || lastNumber > 9999 ) {
		Com_sprintf( fileName, MAX_OSPATH, "screenshots/shot9999%s",psExt );
		return;
	}

	a = lastNumber / 1000;
	lastNumber -= a*1000;
	b = lastNumber / 100;
	lastNumber -= b*100;
	c = lastNumber / 10;
	lastNumber -= c*10;
	d = lastNumber;

	Com_sprintf( fileName, MAX_OSPATH, "screenshots/shot%i%i%i%i%s"
		, a, b, c, d, psExt );
}

/*
====================
R_LevelShot

levelshots are specialized 256*256 thumbnails for
the menu system, sampled down from full screen distorted images
====================
*/
#define LEVELSHOTSIZE 256
static void R_LevelShot( void ) {
	char		checkname[MAX_OSPATH];
	byte		*buffer;
	byte		*source;
	byte		*src, *dst;
	int			x, y;
	int			r, g, b;
	float		xScale, yScale;
	int			xx, yy;

	sprintf( checkname, "levelshots/%s.tga", tr.world->baseName );

	source = (unsigned char *)ri.Hunk_AllocateTempMemory( glConfig.vidWidth * glConfig.vidHeight * 3 );

	buffer = (unsigned char *)ri.Hunk_AllocateTempMemory( LEVELSHOTSIZE * LEVELSHOTSIZE*3 + 18);
	Com_Memset (buffer, 0, 18);
	buffer[2] = 2;		// uncompressed type
	buffer[12] = LEVELSHOTSIZE & 255;
	buffer[13] = LEVELSHOTSIZE >> 8;
	buffer[14] = LEVELSHOTSIZE & 255;
	buffer[15] = LEVELSHOTSIZE >> 8;
	buffer[16] = 24;	// pixel size

	qglReadPixels( 0, 0, glConfig.vidWidth, glConfig.vidHeight, GL_RGB, GL_UNSIGNED_BYTE, source );

	// resample from source
	xScale = glConfig.vidWidth / (4.0*LEVELSHOTSIZE);
	yScale = glConfig.vidHeight / (3.0*LEVELSHOTSIZE);
	for ( y = 0 ; y < LEVELSHOTSIZE ; y++ ) {
		for ( x = 0 ; x < LEVELSHOTSIZE ; x++ ) {
			r = g = b = 0;
			for ( yy = 0 ; yy < 3 ; yy++ ) {
				for ( xx = 0 ; xx < 4 ; xx++ ) {
					src = source + 3 * ( glConfig.vidWidth * (int)( (y*3+yy)*yScale ) + (int)( (x*4+xx)*xScale ) );
					r += src[0];
					g += src[1];
					b += src[2];
				}
			}
			dst = buffer + 18 + 3 * ( y * LEVELSHOTSIZE + x );
			dst[0] = b / 12;
			dst[1] = g / 12;
			dst[2] = r / 12;
		}
	}

	// gamma correct
	if ( ( tr.overbrightBits > 0 ) && glConfig.deviceSupportsGamma ) {
		R_GammaCorrect( buffer + 18, LEVELSHOTSIZE * LEVELSHOTSIZE * 3 );
	}

	ri.FS_WriteFile( checkname, buffer, LEVELSHOTSIZE * LEVELSHOTSIZE*3 + 18 );

	ri.Hunk_FreeTempMemory( buffer );
	ri.Hunk_FreeTempMemory( source );

	ri.Printf( PRINT_ALL, "Wrote %s\n", checkname );
}

/*
==================
R_ScreenShotTGA_f

screenshot
screenshot [silent]
screenshot [levelshot]
screenshot [filename]

Doesn't print the pacifier message if there is a second arg
==================
*/
void R_ScreenShotTGA_f (void) {
	char		checkname[MAX_OSPATH];
	static	int	lastNumber = -1;
	qboolean	silent;

	if ( !strcmp( ri.Cmd_Argv(1), "levelshot" ) ) {
		R_LevelShot();
		return;
	}

	if ( !strcmp( ri.Cmd_Argv(1), "silent" ) ) {
		silent = qtrue;
	} else {
		silent = qfalse;
	}

	if ( ri.Cmd_Argc() == 2 && !silent ) {
		// explicit filename
		Com_sprintf( checkname, MAX_OSPATH, "screenshots/%s.tga", ri.Cmd_Argv( 1 ) );
	} else {
		// scan for a free filename

		// if we have saved a previous screenshot, don't scan
		// again, because recording demo avis can involve
		// thousands of shots
		if ( lastNumber == -1 ) {
			lastNumber = 0;
		}
		// scan for a free number
		for ( ; lastNumber <= 9999 ; lastNumber++ ) {
			R_ScreenshotFilename( lastNumber, checkname, ".tga" );

			if (!ri.FS_FileExists( checkname ))
			{
				break; // file doesn't exist
			}
		}

		if ( lastNumber >= 9999 ) {
			ri.Printf (PRINT_ALL, "ScreenShot: Couldn't create a file\n");
			return;
 		}

		lastNumber++;
	}


	R_TakeScreenshot( 0, 0, glConfig.vidWidth, glConfig.vidHeight, checkname );

	if ( !silent ) {
		ri.Printf (PRINT_ALL, "Wrote %s\n", checkname);
	}
}

//jpeg  vession
void R_ScreenShot_f (void) {
	char		checkname[MAX_OSPATH];
	static	int	lastNumber = -1;
	qboolean	silent;

	if ( !strcmp( ri.Cmd_Argv(1), "levelshot" ) ) {
		R_LevelShot();
		return;
	}
	if ( !strcmp( ri.Cmd_Argv(1), "silent" ) ) {
		silent = qtrue;
	} else {
		silent = qfalse;
	}

	if ( ri.Cmd_Argc() == 2 && !silent ) {
		// explicit filename
		Com_sprintf( checkname, MAX_OSPATH, "screenshots/%s.jpg", ri.Cmd_Argv( 1 ) );
	} else {
		// scan for a free filename

		// if we have saved a previous screenshot, don't scan
		// again, because recording demo avis can involve
		// thousands of shots
		if ( lastNumber == -1 ) {
			lastNumber = 0;
		}
		// scan for a free number
		for ( ; lastNumber <= 9999 ; lastNumber++ ) {
			R_ScreenshotFilename( lastNumber, checkname, ".jpg" );

			if (!ri.FS_FileExists( checkname ))
			{
				break; // file doesn't exist
			}
		}

		if ( lastNumber == 10000 ) {
			ri.Printf (PRINT_ALL, "ScreenShot: Couldn't create a file\n");
			return;
 		}

		lastNumber++;
	}


	R_TakeScreenshotJPEG( 0, 0, glConfig.vidWidth, glConfig.vidHeight, checkname );

	if ( !silent ) {
		ri.Printf (PRINT_ALL, "Wrote %s\n", checkname);
	}
}

//============================================================================

/*
** GL_SetDefaultState
*/
void GL_SetDefaultState( void )
{
	qglClearDepth( 1.0f );

	qglCullFace(GL_FRONT);

	qglColor4f (1,1,1,1);

	// initialize downstream texture unit if we're running
	// in a multitexture environment
	if ( qglActiveTextureARB ) {
		GL_SelectTexture( 1 );
		GL_TextureMode( r_textureMode->string );
		GL_TexEnv( GL_MODULATE );
		qglDisable( GL_TEXTURE_2D );
		GL_SelectTexture( 0 );
	}

	qglEnable(GL_TEXTURE_2D);
	GL_TextureMode( r_textureMode->string );
	GL_TexEnv( GL_MODULATE );

	qglShadeModel( GL_SMOOTH );
	qglDepthFunc( GL_LEQUAL );

	// the vertex array is always enabled, but the color and texture
	// arrays are enabled and disabled around the compiled vertex array call
	qglEnableClientState (GL_VERTEX_ARRAY);

	//
	// make sure our GL state vector is set correctly
	//
	glState.glStateBits = GLS_DEPTHTEST_DISABLE | GLS_DEPTHMASK_TRUE;

	qglPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	qglDepthMask( GL_TRUE );
	qglDisable( GL_DEPTH_TEST );
	qglEnable( GL_SCISSOR_TEST );
	qglDisable( GL_CULL_FACE );
	qglDisable( GL_BLEND );
}


/*
================
GfxInfo_f
================
*/
#ifdef JKA_DYNAMIC_GLOW
extern bool g_bTextureRectangleHack;
#endif
void GfxInfo_f( void )
{
	const char *enablestrings[] =
	{
		"disabled",
		"enabled"
	};
	const char *fsstrings[] =
	{
		"windowed",
		"fullscreen"
	};

	const char *tc_table[] =
	{
		"None",
		"GL_S3_s3tc",
		"GL_EXT_texture_compression_s3tc",
	};

	ri.Printf( PRINT_ALL, "\nGL_VENDOR: %s\n", glConfig.vendor_string );
	ri.Printf( PRINT_ALL, "GL_RENDERER: %s\n", glConfig.renderer_string );
	ri.Printf( PRINT_ALL, "GL_VERSION: %s\n", glConfig.version_string );
	ri.Printf( PRINT_ALL, "GL_EXTENSIONS: %s\n", glConfig.extensions_string );
	ri.Printf( PRINT_ALL, "GL_MAX_TEXTURE_SIZE: %d\n", glConfig.maxTextureSize );
	ri.Printf( PRINT_ALL, "GL_MAX_ACTIVE_TEXTURES_ARB: %d\n", glConfig.maxActiveTextures );
	ri.Printf( PRINT_ALL, "\nPIXELFORMAT: color(%d-bits) Z(%d-bit) stencil(%d-bits)\n", glConfig.colorBits, glConfig.depthBits, glConfig.stencilBits );
	ri.Printf( PRINT_ALL, "MODE: %d, %d x %d %s hz:", r_mode->integer, glConfig.vidWidth, glConfig.vidHeight, fsstrings[r_fullscreen->integer == 1] );
	if ( glConfig.displayFrequency )
	{
		ri.Printf( PRINT_ALL, "%d\n", glConfig.displayFrequency );
	}
	else
	{
		ri.Printf( PRINT_ALL, "N/A\n" );
	}

	// ouned: gamma correction
	if (glConfig.deviceSupportsPostprocessingGamma) {
		ri.Printf(PRINT_ALL, "GAMMA_METHOD: postprocessing\n");
	}
	if (glConfig.deviceSupportsGamma) {
		ri.Printf(PRINT_ALL, "GAMMA_METHOD: hardware\n");
	}

	// rendering primitives
	{
		int		primitives;

		// default is to use triangles if compiled vertex arrays are present
		ri.Printf( PRINT_ALL, "rendering primitives: " );
		primitives = r_primitives->integer;
		if ( primitives == 0 ) {
			if ( qglLockArraysEXT ) {
				primitives = 2;
			} else {
				primitives = 1;
			}
		}
		if ( primitives == -1 ) {
			ri.Printf( PRINT_ALL, "none\n" );
		} else if ( primitives == 2 ) {
			ri.Printf( PRINT_ALL, "single glDrawElements\n" );
		} else if ( primitives == 1 ) {
			ri.Printf( PRINT_ALL, "multiple glArrayElement\n" );
		} else if ( primitives == 3 ) {
			ri.Printf( PRINT_ALL, "multiple glColor4ubv + glTexCoord2fv + glVertex3fv\n" );
		}
	}

	ri.Printf( PRINT_ALL, "texturemode: %s\n", r_textureMode->string );
	ri.Printf( PRINT_ALL, "picmip: %d\n", r_picmip->integer );
	ri.Printf( PRINT_ALL, "texture bits: %d\n", r_texturebits->integer );
	ri.Printf( PRINT_ALL, "lightmap texture bits: %d\n", r_texturebitslm->integer );
	ri.Printf( PRINT_ALL, "multitexture: %s\n", enablestrings[qglActiveTextureARB != 0] );
	ri.Printf( PRINT_ALL, "compiled vertex arrays: %s\n", enablestrings[qglLockArraysEXT != 0 ] );
	ri.Printf( PRINT_ALL, "texenv add: %s\n", enablestrings[glConfig.textureEnvAddAvailable != 0] );
	ri.Printf( PRINT_ALL, "compressed textures: %s\n", enablestrings[glConfig.textureCompression != TC_NONE] );
	ri.Printf( PRINT_ALL, "compressed lightmaps: %s\n", enablestrings[(r_ext_compressed_lightmaps->integer != 0 && glConfig.textureCompression != TC_NONE)] );
	ri.Printf( PRINT_ALL, "texture compression method: %s\n", tc_table[glConfig.textureCompression] );
	ri.Printf( PRINT_ALL, "anisotropic filtering: %s\n", enablestrings[(r_ext_texture_filter_anisotropic->integer != 0) && glConfig.textureFilterAnisotropicAvailable] );
#ifdef JKA_DYNAMIC_GLOW
	ri.Printf( PRINT_ALL, "Dynamic Glow: %s\n", enablestrings[r_DynamicGlow->integer] );
	if (g_bTextureRectangleHack) ri.Printf( PRINT_ALL, "Dynamic Glow ATI BAD DRIVER HACK %s\n", enablestrings[g_bTextureRectangleHack] );
#endif

	if ( glConfig.smpActive ) {
		ri.Printf( PRINT_ALL, "Using dual processor acceleration\n" );
	}
	if ( r_finish->integer ) {
		ri.Printf( PRINT_ALL, "Forcing glFinish\n" );
	}
	if ( r_displayRefresh ->integer ) {
		ri.Printf( PRINT_ALL, "Display refresh set to %d\n", r_displayRefresh->integer );
	}
	if (tr.world)
	{
		ri.Printf( PRINT_ALL, "Light Grid size set to (%.2f %.2f %.2f)\n", tr.world->lightGridSize[0], tr.world->lightGridSize[1], tr.world->lightGridSize[2] );
	}
}

#endif // !DEDICATED
/*
===============
R_Register
===============
*/
void R_Register( void )
{
	//
	// latched and archived variables
	//

	// ouned: atleast fedora has problems with this..
	// ouned: fuck you fedora
//#ifndef __linux__
	r_allowExtensions = ri.Cvar_Get("r_allowExtensions", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
//#else
//	r_allowExtensions = ri.Cvar_Get("r_allowExtensions", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
//#endif

	r_ext_compressed_textures = ri.Cvar_Get("r_ext_compress_textures", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_ext_compressed_lightmaps = ri.Cvar_Get("r_ext_compress_lightmaps", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_ext_preferred_tc_method = ri.Cvar_Get("r_ext_preferred_tc_method", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_ext_gamma_control = ri.Cvar_Get("r_ext_gamma_control", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_ext_multitexture = ri.Cvar_Get("r_ext_multitexture", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_ext_compiled_vertex_array = ri.Cvar_Get("r_ext_compiled_vertex_array", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_ext_texture_env_add = ri.Cvar_Get("r_ext_texture_env_add", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_ext_texture_filter_anisotropic = ri.Cvar_Get("r_ext_texture_filter_anisotropic", "1", CVAR_ARCHIVE | CVAR_GLOBAL);

#ifdef JKA_DYNAMIC_GLOW
	r_DynamicGlow = ri.Cvar_Get( "r_DynamicGlow", "0", CVAR_ARCHIVE | CVAR_GLOBAL );
	r_DynamicGlowPasses = ri.Cvar_Get("r_DynamicGlowPasses", "5", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_DynamicGlowDelta = ri.Cvar_Get("r_DynamicGlowDelta", "0.8f", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_DynamicGlowIntensity = ri.Cvar_Get("r_DynamicGlowIntensity", "1.13f", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_DynamicGlowSoft = ri.Cvar_Get("r_DynamicGlowSoft", "1", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_DynamicGlowWidth = ri.Cvar_Get("r_DynamicGlowWidth", "320", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_DynamicGlowHeight = ri.Cvar_Get("r_DynamicGlowHeight", "240", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
#endif


	r_picmip = ri.Cvar_Get("r_picmip", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_colorMipLevels = ri.Cvar_Get ("r_colorMipLevels", "0", CVAR_LATCH );
	AssertCvarRange( r_picmip, 0, 16, qtrue );
	r_detailTextures = ri.Cvar_Get("r_detailtextures", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_texturebits = ri.Cvar_Get("r_texturebits", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_texturebitslm = ri.Cvar_Get("r_texturebitslm", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_colorbits = ri.Cvar_Get("r_colorbits", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_stereo = ri.Cvar_Get("r_stereo", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_stencilbits = ri.Cvar_Get("r_stencilbits", "8", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_depthbits = ri.Cvar_Get("r_depthbits", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_overBrightBits = ri.Cvar_Get("r_overBrightBits", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_intensity = ri.Cvar_Get("r_intensity", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_mode = ri.Cvar_Get("r_mode", "-2", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_aspectratio = ri.Cvar_Get("r_aspectratio", "-1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH); // ouned: screen resolutions
	r_fullscreen = ri.Cvar_Get("r_fullscreen", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_customwidth = ri.Cvar_Get("r_customwidth", "1600", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_customheight = ri.Cvar_Get("r_customheight", "1024", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_customaspect = ri.Cvar_Get("r_customaspect", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_simpleMipMaps = ri.Cvar_Get("r_simpleMipMaps", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_vertexLight = ri.Cvar_Get("r_vertexLight", "0", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_uiFullScreen = ri.Cvar_Get( "r_uifullscreen", "0", 0);
	r_subdivisions = ri.Cvar_Get("r_subdivisions", "4", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);
	r_smp = ri.Cvar_Get( "r_smp", "0", CVAR_ROM);
	r_ignoreFastPath = ri.Cvar_Get("r_ignoreFastPath", "1", CVAR_ARCHIVE | CVAR_GLOBAL | CVAR_LATCH);

	//
	// temporary latched variables that can only change over a restart
	//
	r_displayRefresh = ri.Cvar_Get( "r_displayRefresh", "0", CVAR_LATCH );
	AssertCvarRange( r_displayRefresh, 0, 200, qtrue );
	r_fullbright = ri.Cvar_Get ("r_fullbright", "0", CVAR_CHEAT );
	r_singleShader = ri.Cvar_Get ("r_singleShader", "0", CVAR_CHEAT | CVAR_LATCH );

	//
	// archived variables that can change at any time
	//
	r_lodCurveError = ri.Cvar_Get("r_lodCurveError", "250", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_lodbias = ri.Cvar_Get("r_lodbias", "0", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_autolodscalevalue = ri.Cvar_Get( "r_autolodscalevalue", "0", CVAR_ROM );

	r_flares = ri.Cvar_Get("r_flares", "0", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_znear = ri.Cvar_Get( "r_znear", "4", CVAR_CHEAT );
	AssertCvarRange( r_znear, 0.001f, 200, qtrue );
	r_ignoreGLErrors = ri.Cvar_Get("r_ignoreGLErrors", "1", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_fastsky = ri.Cvar_Get("r_fastsky", "0", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_inGameVideo = ri.Cvar_Get("r_inGameVideo", "1", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_drawSun = ri.Cvar_Get("r_drawSun", "0", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_dynamiclight = ri.Cvar_Get("r_dynamiclight", "1", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_dlightBacks = ri.Cvar_Get("r_dlightBacks", "1", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_finish = ri.Cvar_Get("r_finish", "0", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_textureMode = ri.Cvar_Get("r_textureMode", "GL_LINEAR_MIPMAP_NEAREST", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_swapInterval = ri.Cvar_Get("r_swapInterval", "0", CVAR_ARCHIVE | CVAR_GLOBAL);

	// ouned: gamma correction
	r_gamma = ri.Cvar_Get("r_gamma", "1", CVAR_ARCHIVE | CVAR_GLOBAL);
	r_gammamethod = ri.Cvar_Get("r_gammamethod", GAMMA_DEFAULT, CVAR_ARCHIVE | CVAR_LATCH | CVAR_GLOBAL);

	r_facePlaneCull = ri.Cvar_Get("r_facePlaneCull", "1", CVAR_ARCHIVE | CVAR_GLOBAL);

	r_primitives = ri.Cvar_Get("r_primitives", "0", CVAR_ARCHIVE | CVAR_GLOBAL);

	r_ambientScale = ri.Cvar_Get( "r_ambientScale", "0.6", CVAR_CHEAT );
	r_directedScale = ri.Cvar_Get( "r_directedScale", "1", CVAR_CHEAT );

	//
	// temporary variables that can change at any time
	//
	r_showImages = ri.Cvar_Get( "r_showImages", "0", CVAR_CHEAT );

	r_debugLight = ri.Cvar_Get( "r_debuglight", "0", CVAR_TEMP );
	r_debugSort = ri.Cvar_Get( "r_debugSort", "0", CVAR_CHEAT );
	r_printShaders = ri.Cvar_Get( "r_printShaders", "0", 0 );

	r_surfaceSprites = ri.Cvar_Get ("r_surfaceSprites", "1", CVAR_TEMP);
	r_surfaceWeather = ri.Cvar_Get ("r_surfaceWeather", "0", CVAR_TEMP);

	r_windSpeed = ri.Cvar_Get ("r_windSpeed", "0", 0);
	r_windAngle = ri.Cvar_Get ("r_windAngle", "0", 0);
	r_windGust = ri.Cvar_Get ("r_windGust", "0", 0);
	r_windDampFactor = ri.Cvar_Get ("r_windDampFactor", "0.1", 0);
	r_windPointForce = ri.Cvar_Get ("r_windPointForce", "0", 0);
	r_windPointX = ri.Cvar_Get ("r_windPointX", "0", 0);
	r_windPointY = ri.Cvar_Get ("r_windPointY", "0", 0);

	r_nocurves = ri.Cvar_Get ("r_nocurves", "0", CVAR_CHEAT );
	r_drawworld = ri.Cvar_Get ("r_drawworld", "1", CVAR_CHEAT );
	r_lightmap = ri.Cvar_Get ("r_lightmap", "0", CVAR_CHEAT );
	r_portalOnly = ri.Cvar_Get ("r_portalOnly", "0", CVAR_CHEAT );

	r_flareSize = ri.Cvar_Get ("r_flareSize", "40", CVAR_CHEAT);
	r_flareFade = ri.Cvar_Get ("r_flareFade", "7", CVAR_CHEAT);

	r_showSmp = ri.Cvar_Get ("r_showSmp", "0", CVAR_CHEAT);
	r_skipBackEnd = ri.Cvar_Get ("r_skipBackEnd", "0", CVAR_CHEAT);

	r_newDLights = ri.Cvar_Get ("r_newDLights", "0", 0);

	r_measureOverdraw = ri.Cvar_Get( "r_measureOverdraw", "0", CVAR_CHEAT );
	r_lodscale = ri.Cvar_Get( "r_lodscale", "5", 0 );
	r_norefresh = ri.Cvar_Get ("r_norefresh", "0", CVAR_CHEAT);
	r_drawentities = ri.Cvar_Get ("r_drawentities", "1", CVAR_CHEAT );
	r_ignore = ri.Cvar_Get( "r_ignore", "1", CVAR_CHEAT );
	r_nocull = ri.Cvar_Get ("r_nocull", "0", CVAR_CHEAT);
	r_novis = ri.Cvar_Get ("r_novis", "0", CVAR_CHEAT);
	r_showcluster = ri.Cvar_Get ("r_showcluster", "0", CVAR_CHEAT);
	r_speeds = ri.Cvar_Get ("r_speeds", "0", CVAR_CHEAT);
	r_verbose = ri.Cvar_Get( "r_verbose", "0", CVAR_CHEAT );
	r_logFile = ri.Cvar_Get( "r_logFile", "0", CVAR_CHEAT );
	r_debugSurface = ri.Cvar_Get ("r_debugSurface", "0", CVAR_CHEAT);
	r_nobind = ri.Cvar_Get ("r_nobind", "0", CVAR_CHEAT);
	r_showtris = ri.Cvar_Get ("r_showtris", "0", CVAR_CHEAT);
	r_showsky = ri.Cvar_Get ("r_showsky", "0", CVAR_CHEAT);
	r_shownormals = ri.Cvar_Get ("r_shownormals", "0", CVAR_CHEAT);
	r_clear = ri.Cvar_Get ("r_clear", "0", CVAR_CHEAT);
	r_offsetFactor = ri.Cvar_Get( "r_offsetfactor", "-1", CVAR_CHEAT );
	r_offsetUnits = ri.Cvar_Get( "r_offsetunits", "-2", CVAR_CHEAT );
	r_drawBuffer = ri.Cvar_Get( "r_drawBuffer", "GL_BACK", CVAR_CHEAT );
	r_lockpvs = ri.Cvar_Get ("r_lockpvs", "0", CVAR_CHEAT);
	r_noportals = ri.Cvar_Get ("r_noportals", "0", CVAR_CHEAT);
	r_shadows = ri.Cvar_Get( "cg_shadows", "1", 0 );

	r_maxpolys = ri.Cvar_Get( "r_maxpolys", va("%d", MAX_POLYS), 0);
	r_maxpolyverts = ri.Cvar_Get( "r_maxpolyverts", va("%d", MAX_POLYVERTS), 0);
/*
Ghoul2 Insert Start
*/
	r_noServerGhoul2 = ri.Cvar_Get( "r_noserverghoul2", "0", CVAR_CHEAT);

	r_Ghoul2AnimSmooth = ri.Cvar_Get( "r_ghoul2animsmooth", ".3", 0 );
	r_Ghoul2UnSqashAfterSmooth = ri.Cvar_Get( "r_ghoul2unsqashaftersmooth", "1", 0 );
/*
Ghoul2 Insert End
*/

	r_modelpoolmegs = Cvar_Get("r_modelpoolmegs", "10", CVAR_ARCHIVE | CVAR_GLOBAL);

	// make sure all the commands added here are also
	// removed in R_Shutdown
#ifndef DEDICATED
	ri.Cmd_AddCommand( "imagelist", R_ImageList_f );
	ri.Cmd_AddCommand( "shaderlist", R_ShaderList_f );
	ri.Cmd_AddCommand( "skinlist", R_SkinList_f );
	ri.Cmd_AddCommand( "screenshot", R_ScreenShot_f );
	ri.Cmd_AddCommand( "screenshot_tga", R_ScreenShotTGA_f );
	ri.Cmd_AddCommand( "gfxinfo", GfxInfo_f );
	ri.Cmd_AddCommand("r_we", R_WorldEffect_f);
	ri.Cmd_AddCommand( "imagecacheinfo", RE_RegisterImages_Info_f);
#endif
	ri.Cmd_AddCommand( "modellist", R_Modellist_f );
	ri.Cmd_AddCommand( "modelist", R_ModeList_f );
	ri.Cmd_AddCommand( "modelcacheinfo", RE_RegisterModels_Info_f);

	r_screenshotJpegQuality = ri.Cvar_Get("r_screenshotJpegQuality", "95", CVAR_ARCHIVE | CVAR_GLOBAL);
}

#ifdef G2_COLLISION_ENABLED
#define G2_VERT_SPACE_SERVER_SIZE 256
#endif

/*
===============
R_Init
===============
*/
void R_Init( void ) {
	int i;
	byte *ptr;

	ri.Printf( PRINT_ALL, "----- R_Init -----\n" );

	// clear all our internal state
	Com_Memset( &tr, 0, sizeof( tr ) );
	Com_Memset( &backEnd, 0, sizeof( backEnd ) );
#ifndef DEDICATED
	Com_Memset( &tess, 0, sizeof( tess ) );
#endif

//	Swap_Init();

#ifndef DEDICATED
	Com_Memset( tess.constantColor255, 255, sizeof( tess.constantColor255 ) );
#endif
	//
	// init function tables
	//
	for ( i = 0; i < FUNCTABLE_SIZE; i++ )
	{
		tr.sinTable[i]		= sin( DEG2RAD( i * 360.0f / ( ( float ) ( FUNCTABLE_SIZE - 1 ) ) ) );
		tr.squareTable[i]	= ( i < FUNCTABLE_SIZE/2 ) ? 1.0f : -1.0f;
		tr.sawToothTable[i] = (float)i / FUNCTABLE_SIZE;
		tr.inverseSawToothTable[i] = 1.0f - tr.sawToothTable[i];

		if ( i < FUNCTABLE_SIZE / 2 )
		{
			if ( i < FUNCTABLE_SIZE / 4 )
			{
				tr.triangleTable[i] = ( float ) i / ( FUNCTABLE_SIZE / 4 );
			}
			else
			{
				tr.triangleTable[i] = 1.0f - tr.triangleTable[i-FUNCTABLE_SIZE / 4];
			}
		}
		else
		{
			tr.triangleTable[i] = -tr.triangleTable[i-FUNCTABLE_SIZE/2];
		}
	}
#ifndef DEDICATED
	R_InitFogTable();

	R_NoiseInit();
#endif
	R_Register();

	max_polys = r_maxpolys->integer;
	if (max_polys < MAX_POLYS)
		max_polys = MAX_POLYS;

	max_polyverts = r_maxpolyverts->integer;
	if (max_polyverts < MAX_POLYVERTS)
		max_polyverts = MAX_POLYVERTS;

	ptr = (unsigned char *)ri.Hunk_Alloc( sizeof( *backEndData[0] ) + sizeof(srfPoly_t) * max_polys + sizeof(polyVert_t) * max_polyverts, h_low);
	backEndData[0] = (backEndData_t *) ptr;
	backEndData[0]->polys = (srfPoly_t *) ((char *) ptr + sizeof( *backEndData[0] ));
	backEndData[0]->polyVerts = (polyVert_t *) ((char *) ptr + sizeof( *backEndData[0] ) + sizeof(srfPoly_t) * max_polys);
	if ( r_smp->integer ) {
		ptr = (unsigned char *)ri.Hunk_Alloc( sizeof( *backEndData[1] ) + sizeof(srfPoly_t) * max_polys + sizeof(polyVert_t) * max_polyverts, h_low);
		backEndData[1] = (backEndData_t *) ptr;
		backEndData[1]->polys = (srfPoly_t *) ((char *) ptr + sizeof( *backEndData[1] ));
		backEndData[1]->polyVerts = (polyVert_t *) ((char *) ptr + sizeof( *backEndData[1] ) + sizeof(srfPoly_t) * max_polys);
	} else {
		backEndData[1] = NULL;
	}
#ifndef DEDICATED
	R_ToggleSmpFrame();

	for(i = 0; i < MAX_LIGHT_STYLES; i++)
	{
		RE_SetLightStyle(i, -1);
	}
	InitOpenGL();

	// ouned: gamma correction
	if (r_gammamethod->integer == GAMMA_POSTPROCESSING && !glConfig.deviceSupportsPostprocessingGamma) {
		r_gammamethod->integer = GAMMA_HARDWARE; // temporary fallback to hardware gamma
	}

	R_InitImages();
	R_InitShaders();
	R_InitSkins();
	R_InitFonts();
#endif
	R_ModelInit();
#ifndef DEDICATED

#ifdef G2_COLLISION_ENABLED
	if (!G2VertSpaceServer)
	{
		G2VertSpaceServer = new CMiniHeap(G2_VERT_SPACE_SERVER_SIZE * 1024);
	}
#endif

	int	err = qglGetError();
	if ( err != GL_NO_ERROR )
		ri.Printf (PRINT_ALL, "glGetError() = 0x%x\n", err);
#endif
	ri.Printf( PRINT_ALL, "----- finished R_Init -----\n" );
}

/*
===============
RE_Shutdown
===============
*/
void RE_Shutdown( qboolean destroyWindow ) {

	ri.Printf( PRINT_ALL, "RE_Shutdown( %i )\n", destroyWindow );

	ri.Cmd_RemoveCommand ("modellist");
	ri.Cmd_RemoveCommand ("screenshotJPEG");
	ri.Cmd_RemoveCommand ("screenshot");
	ri.Cmd_RemoveCommand ("imagelist");
	ri.Cmd_RemoveCommand ("shaderlist");
	ri.Cmd_RemoveCommand ("skinlist");
	ri.Cmd_RemoveCommand ("gfxinfo");
	ri.Cmd_RemoveCommand ("modelist");
	ri.Cmd_RemoveCommand ("shaderstate");
	ri.Cmd_RemoveCommand ("r_we");
	ri.Cmd_RemoveCommand ("modelcacheinfo");
	ri.Cmd_RemoveCommand ("imagecacheinfo");
#ifndef DEDICATED
#ifdef JKA_DYNAMIC_GLOW // GLOWXXX
	if ( r_DynamicGlow && r_DynamicGlow->integer )
	{
		// Release the Glow Vertex Shader.
		if ( tr.glowVShader )
		{
			qglDeleteProgramsARB( 1, &tr.glowVShader );
		}

		// Release Pixel Shader.
		if ( tr.glowPShader )
		{
			if ( qglCombinerParameteriNV  )
			{
				// Release the Glow Regcom call list.
				qglDeleteLists( tr.glowPShader, 1 );
			}
			else if ( qglGenProgramsARB )
			{
				// Release the Glow Fragment Shader.
				qglDeleteProgramsARB( 1, &tr.glowPShader );
			}
		}

		// Release the scene glow texture.
		qglDeleteTextures( 1, &tr.screenGlow );

		// Release the scene texture.
		qglDeleteTextures( 1, &tr.sceneImage );

		// Release the blur texture.
		qglDeleteTextures( 1, &tr.blurImage );
	}
#endif

	// ouned: gamma correction
	if (tr.m_hVShader) {
		qglDetachObjectARB(tr.gammaProgram, tr.m_hVShader);
		qglDeleteObjectARB(tr.m_hVShader);

		tr.m_hVShader = 0;
	}
	if (tr.m_hFShader) {
		qglDetachObjectARB(tr.gammaProgram, tr.m_hFShader);
		qglDeleteObjectARB(tr.m_hFShader);

		tr.m_hFShader = 0;
	}

	if (tr.gammaProgram) {
		qglDeleteObjectARB(tr.gammaProgram);
		tr.gammaProgram = 0;
	}

	if (tr.gammaRenderTarget) {
		qglDeleteTextures(1, &tr.gammaRenderTarget);
	}

	if (tr.gammaRenderDepthBuffer) {
		qglDeleteRenderbuffersEXT(1, &tr.gammaRenderDepthBuffer);
	}

	if (tr.gammaFramebuffer) {
		qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		qglDeleteFramebuffersEXT(1, &tr.gammaFramebuffer);
	}
	// --------

	R_ShutdownFonts();
	if ( tr.registered ) {
		R_SyncRenderThread();
		R_ShutdownCommandBuffers();
		if (destroyWindow)
		{
			R_DeleteTextures();		// only do this for vid_restart now, not during things like map load
		}
	}

	// shut down platform specific OpenGL stuff
	if ( destroyWindow ) {
		GLimp_Shutdown();
	}
#endif //!DEDICATED

	tr.registered = qfalse;

#ifdef G2_COLLISION_ENABLED
	if (G2VertSpaceServer)
	{
		delete G2VertSpaceServer;
		G2VertSpaceServer = 0;
	}
#endif
}

#ifndef DEDICATED

/*
=============
RE_EndRegistration

Touch all images to make sure they are resident
=============
*/
void RE_EndRegistration( void ) {
	R_SyncRenderThread();
}

void RE_GetLightStyle(int style, color4ub_t color)
{
	if (style >= MAX_LIGHT_STYLES)
	{
		ri.Error( ERR_FATAL, "RE_GetLightStyle: %d is out of range", (int)style );
		return;
	}

	*(int *)color = *(int *)styleColors[style];
}

void RE_SetLightStyle(int style, int color)
{
	if (style >= MAX_LIGHT_STYLES)
	{
		ri.Error( ERR_FATAL, "RE_SetLightStyle: %d is out of range", (int)style );
		return;
	}

	if (*(int*)styleColors[style] != color)
	{
		*(int *)styleColors[style] = color;
	}
}

#endif //!DEDICATED
/*
@@@@@@@@@@@@@@@@@@@@@
GetRefAPI

@@@@@@@@@@@@@@@@@@@@@
*/
refexport_t *GetRefAPI ( int apiVersion, refimport_t *rimp ) {
	static refexport_t	re;

	ri = *rimp;

	Com_Memset( &re, 0, sizeof( re ) );

	if ( apiVersion != REF_API_VERSION ) {
		ri.Printf(PRINT_ALL, "Mismatched REF_API_VERSION: expected %i, got %i\n",
			REF_API_VERSION, apiVersion );
		return NULL;
	}

	// the RE_ functions are Renderer Entry points

	re.Shutdown = RE_Shutdown;
#ifndef DEDICATED
	re.BeginRegistration = RE_BeginRegistration;
	re.RegisterModel = RE_RegisterModel;
	re.RegisterSkin = RE_RegisterSkin;
	re.RegisterShader = RE_RegisterShader;
	re.RegisterShaderNoMip = RE_RegisterShaderNoMip;
	re.LoadWorld = RE_LoadWorldMap;
	re.SetWorldVisData = RE_SetWorldVisData;
	re.EndRegistration = RE_EndRegistration;

	re.BeginFrame = RE_BeginFrame;
	re.EndFrame = RE_EndFrame;

	re.MarkFragments = R_MarkFragments;
	re.LerpTag = R_LerpTag;
	re.ModelBounds = R_ModelBounds;

	re.DrawRotatePic = RE_RotatePic;
	re.DrawRotatePic2 = RE_RotatePic2;

	re.ClearScene = RE_ClearScene;
	re.AddRefEntityToScene = RE_AddRefEntityToScene;
	re.AddMiniRefEntityToScene = RE_AddMiniRefEntityToScene;
	re.AddPolyToScene = RE_AddPolyToScene;
	re.LightForPoint = R_LightForPoint;
	re.AddLightToScene = RE_AddLightToScene;
	re.AddAdditiveLightToScene = RE_AddAdditiveLightToScene;
	re.RenderScene = RE_RenderScene;

	re.SetColor = RE_SetColor;
	re.DrawStretchPic = RE_StretchPic;
	re.DrawStretchRaw = RE_StretchRaw;
	re.UploadCinematic = RE_UploadCinematic;

	re.RegisterFont = RE_RegisterFont;
	re.Font_StrLenPixels = RE_Font_StrLenPixels;
	re.Font_StrLenChars = RE_Font_StrLenChars;
	re.Font_HeightPixels = RE_Font_HeightPixels;
	re.Font_DrawString = RE_Font_DrawString;
	re.Language_IsAsian = Language_IsAsian;
	re.Language_UsesSpaces = Language_UsesSpaces;
	re.AnyLanguage_ReadCharFromString = AnyLanguage_ReadCharFromString;

	re.RemapShader = R_RemapShader;
	re.GetEntityToken = R_GetEntityToken;
	re.inPVS = R_inPVS;

	re.GetLightStyle = RE_GetLightStyle;
	re.SetLightStyle = RE_SetLightStyle;

	re.GetBModelVerts = RE_GetBModelVerts;
#endif //!DEDICATED
	return &re;
}

