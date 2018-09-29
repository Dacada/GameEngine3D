#include <engine3D_main.h>

#include <engine3D_mesh.h>
#include <engine3D_shader.h>
#include <engine3D_phongShader.h>
#include <engine3D_resourceLoader.h>
#include <engine3D_vertex.h>
#include <engine3D_input.h>
#include <engine3D_time.h>
#include <engine3D_transform.h>
#include <engine3D_camera.h>
#include <engine3D_texture.h>
#include <engine3D_util.h>
#include <engine3D_renderUtil.h>

#include <stdbool.h>
#include <stdlib.h>

#include <math.h>

static engine3D_mesh_t mesh;
static engine3D_phongShader_t shader;
static engine3D_transform_t transform;
static engine3D_material_t material;

static engine3D_texture_t texture;
static engine3D_vector3f_t color;

static void init(void) {
	engine3D_phongShader_init(&shader);
	engine3D_transform_reset(&transform);
	transform.translation.z = 5;

	color.x = 0; color.y = 1; color.z = 1;
	engine3D_resourceLoader_loadTexture("test.png", &texture);
	material.texture = &texture;
	material.color = &color;
	material.specularIntensity = 2;
	material.specularPower = 32;

	engine3D_resourceLoader_loadMesh("tetrahedron.obj", &mesh);
	//engine3D_mesh_init(&mesh);
	//engine3D_vertex_t vertices[] = { { {-1, -1, 0},{0, 0},{0, 0, 0} },{ {0, 1, 0},{0.5f, 0},{0, 0, 0} },{ {1, -1, 0},{1, 0},{0, 0, 0} },{ {0, -1, 1},{0, 0.5f},{0, 0, 0} } };
	//unsigned int indices[] = { 3,1,0, 2,1,3, 0,1,2, 0,2,3 };
	//engine3D_mesh_addVertices(&mesh, vertices, 4, indices, 12, true);

	engine3D_transform_zNear = 0.1f;
	engine3D_transform_zFar = 1000.0f;
	engine3D_transform_width = engine3D_width;
	engine3D_transform_height = engine3D_height;
	engine3D_transform_fov = 70.0f;
	engine3D_camera_init(&engine3D_transform_camera);

	engine3D_phongShader_ambientLight.x = 0.1f;
	engine3D_phongShader_ambientLight.y = 0.1f;
	engine3D_phongShader_ambientLight.z = 0.1f;

	engine3D_phongShader_directionalLight.base.color.x = 1;
	engine3D_phongShader_directionalLight.base.color.y = 1;
	engine3D_phongShader_directionalLight.base.color.z = 1;
	engine3D_phongShader_directionalLight.base.intensity = 0.8f;
	engine3D_phongShader_directionalLight.direction.x = 1;
	engine3D_phongShader_directionalLight.direction.y = 1;
	engine3D_phongShader_directionalLight.direction.z = 1;
	engine3D_vector3f_normalize(&engine3D_phongShader_directionalLight.direction);
}

static void generalInput(float delta) {
	(void)delta;

	if (engine3D_input_getKey(GLFW_KEY_ESCAPE)) {
		exit(EXIT_SUCCESS);
	}
}

static void cameraInput(float delta) {
	float sensitivity = 0.5f;
	float movAmt = delta * 10;

	static bool movingCamera = false;
	static engine3D_vector2f_t centerPosition;
	if (engine3D_input_getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		engine3D_input_setCursor(ENGINE3D_CURSOR_DISABLED);
		engine3D_input_getMousePosition(&centerPosition);
		movingCamera = true;
	}

	if (engine3D_input_getMouseUp(GLFW_MOUSE_BUTTON_1)) {
		engine3D_input_setCursor(ENGINE3D_CURSOR_ENABLED);
		movingCamera = false;
	}

	if (engine3D_input_getKey(GLFW_KEY_W)) {
		engine3D_camera_move(&engine3D_transform_camera, &engine3D_transform_camera.forward, movAmt);
	}
	if (engine3D_input_getKey(GLFW_KEY_S)) {
		engine3D_camera_move(&engine3D_transform_camera, &engine3D_transform_camera.forward, -movAmt);
	}
	if (engine3D_input_getKey(GLFW_KEY_A)) {
		engine3D_vector3f_t vec;
		engine3D_camera_left(&engine3D_transform_camera, &vec);
		engine3D_camera_move(&engine3D_transform_camera, &vec, movAmt);
	}
	if (engine3D_input_getKey(GLFW_KEY_D)) {
		engine3D_vector3f_t vec;
		engine3D_camera_right(&engine3D_transform_camera, &vec);
		engine3D_camera_move(&engine3D_transform_camera, &vec, movAmt);
	}

	if (movingCamera) {
		engine3D_vector2f_t pos, deltaPos;
		engine3D_input_getMousePosition(&pos);
		engine3D_vector2f_sub(&pos, &centerPosition, &deltaPos);

		if (deltaPos.x != 0)
		{
			engine3D_camera_rotateY(&engine3D_transform_camera, deltaPos.x * sensitivity * delta);
		}

		if (deltaPos.y != 0)
		{
			engine3D_camera_rotateX(&engine3D_transform_camera, deltaPos.y * sensitivity * delta);
		}
	}
}

static void input(void) {

	float t = engine3D_time_getDelta();

	generalInput(t);
	cameraInput(t);
}

static void update(void) {
	static float tmp = 0.0f;
	tmp += engine3D_time_getDelta();

	float sinTmp = sinf(tmp);

	transform.translation.x = sinTmp;
	transform.translation.y = 0;
	transform.translation.z = 5;
	transform.rotation.x = 0;
	transform.rotation.y = sinTmp * 180;
	transform.rotation.z = 0;
	//transform.scale.x = sinTmp;
	//transform.scale.y = sinTmp;
	//transform.scale.z = sinTmp;
}

static void render(void) {
	engine3D_vector3f_t v1, v2;
	engine3D_vector3f_divf(&engine3D_transform_camera.pos, 2048, &v1);
	engine3D_vector3f_abs(&v1, &v2);
	engine3D_renderUtils_setClearColor(&v2);

	engine3D_shader_bind((engine3D_shader_t *)&shader);

	engine3D_matrix4f_t transformation, projectedTransformation;
	engine3D_transform_getTransformation(&transform, &transformation);
	engine3D_transform_getProjectedTransformation(&transform, &projectedTransformation);
	engine3D_phongShader_updateUniforms(&shader, &transformation, &projectedTransformation, &material);

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
