#include <engine3D_phongShader.h>
#include <engine3D_shader.h>
#include <engine3D_resourceLoader.h>
#include <engine3D_renderUtil.h>
#include <engine3D_transform.h>

engine3D_vector3f_t engine3D_phongShader_ambientLight;
engine3D_phongShader_directionalLight_t engine3D_phongShader_directionalLight;

engine3D_phongShader_t *engine3D_phongShader_init(engine3D_phongShader_t *const shader) {
	engine3D_shader_init((engine3D_shader_t*)shader);

	char shaderText[65536];
	engine3D_shader_addVertexShader(engine3D_resourceLoader_loadShader("phongVertex.vs", shaderText, 65536), (engine3D_shader_t*)shader);
	engine3D_shader_addFragmentShader(engine3D_resourceLoader_loadShader("phongFragment.fs", shaderText, 65536), (engine3D_shader_t*)shader);
	engine3D_shader_compile((engine3D_shader_t*)shader);

	engine3D_shader_addUniform("transform", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("transformProjected", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("baseColor", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("ambientLight", (engine3D_shader_t*)shader);

	engine3D_shader_addUniform("directionalLight.base.color", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("directionalLight.base.intensity", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("directionalLight.direction", (engine3D_shader_t*)shader);

	engine3D_shader_addUniform("specularIntensity", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("specularPower", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("eyePos", (engine3D_shader_t*)shader);

	return shader;
}

void engine3D_phongShader_updateUniforms(engine3D_phongShader_t * const shader, const engine3D_matrix4f_t *const worldMatrix, const engine3D_matrix4f_t *projectedMatrix, const engine3D_material_t *const material) {
	(void)worldMatrix;

	if (material->texture != NULL)
		engine3D_texture_bind(material->texture);
	else
		engine3D_renderUtil_unbindTextures();

	engine3D_shader_setUniformMat4f("transform", worldMatrix, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformMat4f("transformProjected", projectedMatrix, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("baseColor", material->color, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("ambientLight", &engine3D_phongShader_ambientLight, (engine3D_shader_t*)shader);

	engine3D_shader_setUniformVec3f("directionalLight.base.color", &engine3D_phongShader_directionalLight.base.color, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformf("directionalLight.base.intensity", engine3D_phongShader_directionalLight.base.intensity, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("directionalLight.direction", &engine3D_phongShader_directionalLight.direction, (engine3D_shader_t*)shader);

	engine3D_shader_setUniformf("specularIntensity", material->specularIntensity, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformf("specularPower", material->specularPower, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("eyePos", &engine3D_transform_camera.pos, (engine3D_shader_t*)shader);
}
