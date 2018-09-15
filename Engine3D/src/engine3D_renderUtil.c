#include <engine3D_renderUtil.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

void engine3D_renderUtil_clearScreen(void) {
	// TODO: Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void engine3D_renderUtil_initGraphics(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// TODO: Depth clamp for later

	glEnable(GL_FRAMEBUFFER_SRGB);
}

const char *engine3D_renderUtil_getOpenGLVersion(void) {
	return (char*)glGetString(GL_VERSION);
}
