#include <engine3D_main.h>

#include <engine3d_mesh.h>
#include <engine3d_vertex.h>
#include <engine3D_input.h>

#include <stdbool.h>
#include <stdlib.h>

void init(void) {
	engine3D_mesh_t mesh;
	engine3D_mesh_init(&mesh);

	engine3D_vertex_t vertices[3] = { { { -1, -1, 0 } },{ { 0, 1, 0 } },{ { 1, -1, 0 } } };
	engine3D_mesh_addVertices(&mesh, vertices, 3);

	engine3D_mesh_draw(&mesh);
}

void input(void) {
	if (engine3D_input_getKeyDown(GLFW_KEY_UP)) {
		printf("We've just pressed up.\n");
	}
	if (engine3D_input_getKeyUp(GLFW_KEY_UP)) {
		printf("We've just released up.\n");
	}

	if (engine3D_input_getMouseDown(GLFW_MOUSE_BUTTON_LEFT)) {
		printf("We've just pressed left click.\n");

		engine3D_vector2f_t pos;
		engine3D_input_getMousePosition(&pos);
		printf("Position: "); engine3D_vector2f_fprintf(stdout, &pos); printf("\n");
	}
	if (engine3D_input_getMouseUp(GLFW_MOUSE_BUTTON_LEFT)) {
		printf("We've just released left click.\n");
	}
}

void update(void) {
}

void render(void) {
}

int main(void) {
	engine3D_setGame_init(init);
	engine3D_setGame_input(input);
	engine3D_setGame_update(update);
	engine3D_setGame_render(render);

	engine3D_init();
	engine3D_start();

	return EXIT_SUCCESS;
}