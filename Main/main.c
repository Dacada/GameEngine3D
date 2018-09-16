#include <engine3D_main.h>

#include <engine3D_mesh.h>
#include <engine3D_shader.h>
#include <engine3D_resourceLoader.h>
#include <engine3D_vertex.h>
#include <engine3D_input.h>
#include <engine3D_time.h>
#include <engine3D_transform.h>

#include <stdbool.h>
#include <stdlib.h>

#include <math.h>

static engine3D_mesh_t mesh;
static engine3D_shader_t shader;
static engine3D_transform_t transform;

static void init(void) {
	engine3D_mesh_init(&mesh);
	engine3D_shader_init(&shader);
	engine3D_transform_init(&transform);

	engine3D_vertex_t vertices[3] = { { { -1, -1, 0 } }, { { 0, 1, 0 } }, { { 1, -1, 0 } } };
	engine3D_mesh_addVertices(&mesh, vertices, 3);

	char shaderText[1024];
	engine3D_shader_addVertexShader(engine3D_resourceLoader_loadShader("basicVertex.vs", shaderText, 1024), &shader);
	engine3D_shader_addFragmentShader(engine3D_resourceLoader_loadShader("basicFragment.fs", shaderText, 1024), &shader);
	engine3D_shader_compile(&shader);

	engine3D_shader_addUniform("transform", &shader);
}

static void input(void) {
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

static void update(void) {
	static float tmp = 0.0f;
	tmp += engine3D_time_getDelta();
	transform.translation.x = sinf(tmp);
	transform.translation.y = 0;
	transform.translation.z = 0;
}

static void render(void) {
	engine3D_shader_bind(&shader);
	engine3D_matrix4f_t transformation;
	engine3D_transform_getTransformation(&transform, &transformation);
	engine3D_shader_setUniformMat4f("transform", &transformation, &shader);
	engine3D_mesh_draw(&mesh);
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
