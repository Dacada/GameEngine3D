#include <engine3D_game.h>
#include <engine3D_input.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

void engine3D_game_init(void) {
}

void engine3D_game_input(void) {
	if (engine3d_input_getKeyDown(GLFW_KEY_UP)) {
		printf("We've just pressed up.\n");
	}
	if (engine3d_input_getKeyUp(GLFW_KEY_UP)) {
		printf("We've just released up.\n");
	}

	if (engine3d_input_getMouseDown(GLFW_MOUSE_BUTTON_LEFT)) {
		printf("We've just pressed left click.\n");

		vector2d_t pos;
		engine3d_input_getMousePosition(&pos);
		printf("Position: "); fprintf_vector2d(stdout, &pos); printf("\n");
	}
	if (engine3d_input_getMouseUp(GLFW_MOUSE_BUTTON_LEFT)) {
		printf("We've just released left click.\n");
	}
}

void engine3D_game_update(void) {
}

void engine3D_game_render(void) {
}
