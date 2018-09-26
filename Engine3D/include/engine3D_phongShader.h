#ifndef ENGINE3D_PHONGSHADER
#define ENGINE3D_PHONGSHADER

#include <engine3D_shader.h>
#include <engine3D_material.h>
#include <engine3D_vector.h>

extern engine3D_vector3f_t engine3D_phongShader_ambientLight;

typedef struct engine3D_phongShader_t {
	engine3D_shader_t shader;
} engine3D_phongShader_t;

engine3D_phongShader_t *engine3D_phongShader_init(engine3D_phongShader_t *const shader);

void engine3D_phongShader_updateUniforms(engine3D_phongShader_t * const shader, const engine3D_matrix4f_t *const worldMatrix, const engine3D_matrix4f_t *projectedMatrix, const engine3D_material_t *const material);

#endif /* ENGINE3D_BASICSHADER */