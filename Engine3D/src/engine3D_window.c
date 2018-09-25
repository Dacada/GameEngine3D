#include <engine3D_window.h>
#include <engine3D_input.h>
#include <engine3D_util.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <stdio.h>
#include <stdbool.h>

static GLFWwindow *window;
static const char *current_title;

GLFWwindow *engine3D_window_create(const int width, const int height, const char *const title) {
	if (!glfwInit()) {
		engine3D_util_bail("failed to initialize glfw");
	}

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		engine3D_util_bail("failed to create glfw window");
	}
	current_title = title;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwSetKeyCallback(window, (GLFWkeyfun)_engine3D_input_keyCallback);
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)_engine3D_input_mouseButtonCallback);
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)_engine3D_input_mousePositionCallback);

	if (glewInit() != GLEW_OK) {
		engine3D_util_bail("failed to initialize glew");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return window;
}

void engine3D_window_update(void) {
#ifndef NDEBUG
	engine3D_util_reportGlError();
#endif

	glfwPollEvents();
	glfwSwapBuffers(window);
}

bool engine3D_window_closeRequested(void) {
	return glfwWindowShouldClose(window) == 1;
}

void engine3D_window_getSize(int *const width, int *const height) {
	glfwGetFramebufferSize(window, width, height);
}

void engine3D_window_destroy(void) {
	glfwTerminate();
}
