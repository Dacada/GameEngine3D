#include <engine3D_util.h>

#include <GL\glew.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void engine3D_util_bail(const char *const message) {
	fputs(message, stderr);
	abort();
}

void engine3D_util_reportGlError(GLenum error) {
	switch (error) {
	case GL_NO_ERROR: break;
	case GL_INVALID_ENUM:
		engine3D_util_errPrintf("WARNING: OpenGL error - GL_INVALID_ENUM");
		break;
	case GL_INVALID_VALUE:
		engine3D_util_errPrintf("WARNING: OpenGL error - GL_INVALID_VALUE");
		break;
	case GL_INVALID_OPERATION:
		engine3D_util_errPrintf("WARNING: OpenGL error - GL_INVALID_OPERATION");
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		engine3D_util_errPrintf("WARNING: OpenGL error - GL_INVALID_FRAMEBUFFER_OPERATION");
		break;
	case GL_OUT_OF_MEMORY:
		engine3D_util_errPrintf("ERROR: OpenGL error - GL_OUT_OF_MEMORY");
		engine3D_util_bail("gl is in an undefined state");
		break;
	default:
		engine3D_util_errPrintf("WARNING: Unknown OpenGL error - %d", error);
		break;
	}
}

int engine3D_util_errPrintf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}
