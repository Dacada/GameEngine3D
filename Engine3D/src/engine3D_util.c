#include <engine3D_util.h>

#include <GL\glew.h>

#include <stdio.h>
#include <stdlib.h>

void engine3D_util_bail(const char *const message) {
	fprintf(stderr, message);
	abort();
}

void engine3D_util_reportGlError(GLenum error) {
	switch (error) {
	case GL_NO_ERROR: break;
	case GL_INVALID_ENUM:
		fprintf(stderr, "WARNING: OpenGL error - GL_INVALID_ENUM");
		break;
	case GL_INVALID_VALUE:
		fprintf(stderr, "WARNING: OpenGL error - GL_INVALID_VALUE");
		break;
	case GL_INVALID_OPERATION:
		fprintf(stderr, "WARNING: OpenGL error - GL_INVALID_OPERATION");
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		fprintf(stderr, "WARNING: OpenGL error - GL_INVALID_FRAMEBUFFER_OPERATION");
		break;
	case GL_OUT_OF_MEMORY:
		fprintf(stderr, "ERROR: OpenGL error - GL_OUT_OF_MEMORY");
		engine3D_util_bail("gl is in an undefined state");
		break;
	default:
		fprintf(stderr, "WARNING: Unknown OpenGL error - %d", error);
		break;
	}
}
