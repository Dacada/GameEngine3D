#include <engine3D_window.h>
#include <engine3D_util.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <gl/GL.h>

#include <stdio.h>
#include <stdbool.h>

static GLFWwindow *window;
static const char *current_title;

void engine3D_window_create(const int width, const int height, const char *const title) {
	if (!glfwInit()) {
		engine3D_util_bail("failed to initialize glfw");
	}

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		engine3D_util_bail("failed to create glfw window");
	}
	current_title = title;

	glfwMakeContextCurrent(window);
	//glfwSetWindowUserPointer(window, ???);
	//glfwSetFramebufferSizeCallback(window, resize_callback);
	//glfwSetKeyCallback(window, key_callback);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetCursorPosCallback(window, cusor_position_callback);

#ifdef ENGINE3D_UNLIMITED_FPS
	glfwSwapInterval(0);
#endif

	if (glewInit() != GLEW_OK) {
		engine3D_util_bail("failed to initialize glew");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef ENGINE3D_OUTPUT_OPENGL_ON_WINDOW_CREATION
	printf("OpenGL - %s\n", glGetString(GL_VERSION));
#endif
}

void engine3D_window_update() {
#ifndef NDEBUG
	GLenum error = glGetError();
	engine3D_util_reportGlError(error);
#endif

	glfwPollEvents();
	glfwSwapBuffers(window);
}

bool engine3D_window_closeRequested() {
	return glfwWindowShouldClose(window) == 1;
}

void engine3D_window_getSize(int *const width, int *const height) {
	glfwGetFramebufferSize(window, width, height);
}

const char *const engine3D_window_getTitle() {
	return current_title;
}

void engine3D_window_destroy() {
	glfwTerminate();
}
