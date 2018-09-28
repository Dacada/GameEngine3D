#include <engine3D_phongShader.h>
#include <engine3D_shader.h>
#include <engine3D_resourceLoader.h>
#include <engine3D_renderUtil.h>

engine3D_vector3f_t engine3D_phongShader_ambientLight;
engine3D_phongShader_directionalLight_t engine3D_phongShader_directionalLight;

engine3D_phongShader_t *engine3D_phongShader_init(engine3D_phongShader_t *const shader) {
	engine3D_shader_init((engine3D_shader_t*)shader);

	char shaderText[1024];
	// Quick fix to use the right shader version in my windows and linux machines.
#ifndef __unix__
	engine3D_shader_addVertexShader(engine3D_resourceLoader_loadShader("phongVertex.vs", shaderText, 1024), (engine3D_shader_t*)shader);
	engine3D_shader_addFragmentShader(engine3D_resourceLoader_loadShader("phongFragment.fs", shaderText, 1024), (engine3D_shader_t*)shader);
#else
	engine3D_shader_addVertexShader(engine3D_resourceLoader_loadShader("phongVertex_ES.vs", shaderText, 1024), (engine3D_shader_t*)shader);
	engine3D_shader_addFragmentShader(engine3D_resourceLoader_loadShader("phongFragment_ES.fs", shaderText, 1024), (engine3D_shader_t*)shader);
#endif
	engine3D_shader_compile((engine3D_shader_t*)shader);

	engine3D_shader_addUniform("transform", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("baseColor", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("ambientLight", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("directionalLight.base.color", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("directionalLight.base.intensity", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("directionalLight.direction", (engine3D_shader_t*)shader);

	return shader;
}

void engine3D_phongShader_updateUniforms(engine3D_phongShader_t * const shader, const engine3D_matrix4f_t *const worldMatrix, const engine3D_matrix4f_t *projectedMatrix, const engine3D_material_t *const material) {
	(void)worldMatrix;

	if (material->texture != NULL)
		engine3D_texture_bind(material->texture);
	else
		engine3D_renderUtil_unbindTextures();

	engine3D_shader_setUniformMat4f("transform", projectedMatrix, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("baseColor", material->color, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("ambientLight", &engine3D_phongShader_ambientLight, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("directionalLight.base.color", engine3D_phongShader_directionalLight.base.color, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformf("directionalLight.base.intensity", engine3D_phongShader_directionalLight.base.intensity, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("directionalLight.direction", engine3D_phongShader_directionalLight.direction, (engine3D_shader_t*)shader);
}
