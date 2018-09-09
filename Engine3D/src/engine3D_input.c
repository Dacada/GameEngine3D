#include <engine3D_input.h>
#include <engine3D_vector.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string.h>

#define LEN_KEYS (GLFW_KEY_LAST + 1)
#define LEN_MOUSE_BUTTONS (GLFW_MOUSE_BUTTON_LAST + 1)

static bool keys[LEN_KEYS];
static bool keysState[LEN_KEYS];
static bool keysDown[LEN_KEYS];
static bool keysUp[LEN_KEYS];

static bool mouseButtons[LEN_MOUSE_BUTTONS];
static bool mouseButtonsState[LEN_MOUSE_BUTTONS];
static bool mouseButtonsDown[LEN_MOUSE_BUTTONS];
static bool mouseButtonsUp[LEN_MOUSE_BUTTONS];

static double lastMousePositionX, lastMousePositionY;

void engine3d_input_update(void) {
	for (int i = 0; i < LEN_KEYS; i++)
	{
		keysDown[i] = keys[i] && !keysState[i];
		keysUp[i] = !keys[i] && keysState[i];
	}
	memcpy(keysState, keys, sizeof(bool)*LEN_KEYS);

	for (int i = 0; i < LEN_MOUSE_BUTTONS; i++)
	{
		mouseButtonsDown[i] = mouseButtons[i] && !mouseButtonsState[i];
		mouseButtonsUp[i] = !mouseButtons[i] && mouseButtonsState[i];
	}
	memcpy(mouseButtonsState, mouseButtons, sizeof(bool)*LEN_MOUSE_BUTTONS);
}

bool engine3d_input_getKey(const int keyCode) {
	if (keyCode < 0 || keyCode > LEN_KEYS)
		return false;
	return keys[keyCode];
}

bool engine3d_input_getKeyDown(const int keyCode) {
	if (keyCode < 0 || keyCode > LEN_KEYS)
		return false;
	return keysDown[keyCode];
}

bool engine3d_input_getKeyUp(const int keyCode) {
	if (keyCode < 0 || keyCode > LEN_KEYS)
		return false;
	return keysUp[keyCode];
}

bool engine3d_input_getMouse(const int mouseButton) {
	if (mouseButton < 0 || mouseButton > LEN_MOUSE_BUTTONS)
		return false;
	return mouseButtons[mouseButton];
}

bool engine3d_input_getMouseDown(const int mouseButton) {
	if (mouseButton < 0 || mouseButton > LEN_MOUSE_BUTTONS)
		return false;
	return mouseButtonsDown[mouseButton];
}

bool engine3d_input_getMouseUp(const int mouseButton) {
	if (mouseButton < 0 || mouseButton > LEN_MOUSE_BUTTONS)
		return false;
	return mouseButtonsUp[mouseButton];
}

void engine3d_input_getMousePosition(vector2d_t *const position) {
	position->x = lastMousePositionX;
	position->y = lastMousePositionY;
}

void _engine3D_input_keyCallback(const GLFWwindow *const window, const int key, const int scancode, const int action, const int mods) {
	if (key < 0 || key > LEN_KEYS)
		return;
	keys[key] = action != GLFW_RELEASE;
}

void _engine3D_input_mouseButtonCallback(const GLFWwindow *const window, const int button, const int action, const int mods) {
	if (button < 0 || button > LEN_MOUSE_BUTTONS)
		return;
	mouseButtons[button] = action != GLFW_RELEASE;
}

void _engine3D_input_mousePositionCallback(const GLFWwindow *const window, const double xpos, const double ypos) {
	lastMousePositionX = xpos;
	lastMousePositionY = ypos;
}
