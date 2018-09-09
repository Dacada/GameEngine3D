#pragma once

#include <engine3D_vector.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <stdbool.h>

void engine3d_input_update(void);

bool engine3d_input_getKey(const int keyCode);

bool engine3d_input_getKeyDown(const int keyCode);

bool engine3d_input_getKeyUp(const int keyCode);

bool engine3d_input_getMouse(const int mouseButton);

bool engine3d_input_getMouseDown(const int mouseButton);

bool engine3d_input_getMouseUp(const int mouseButton);

void engine3d_input_getMousePosition(vector2d_t *const position);

void _engine3D_input_keyCallback(const GLFWwindow *const window, const int key, const int scancode, const int action, const int mods);

void _engine3D_input_mouseButtonCallback(const GLFWwindow *const window, const int button, const int action, const int mods);

void _engine3D_input_mousePositionCallback(const GLFWwindow *const window, const double xpos, const double ypos);
