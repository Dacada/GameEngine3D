#include <engine3D_basicShader.h>
#include <engine3D_renderUtil.h>

engine3D_basicShader_t *engine3D_basicShader_init(engine3D_basicShader_t *const shader) {
	engine3D_shader_init((engine3D_shader_t*)shader);

	char shaderText[1024];
	// Quick fix to use the right shader version in my windows and linux machines.
#ifndef __unix__
	engine3D_shader_addVertexShader(engine3D_resourceLoader_loadShader("basicVertex.vs", shaderText, 1024), (engine3D_shader_t*)shader);
	engine3D_shader_addFragmentShader(engine3D_resourceLoader_loadShader("basicFragment.fs", shaderText, 1024), (engine3D_shader_t*)shader);
#else
	engine3D_shader_addVertexShader(engine3D_resourceLoader_loadShader("basicVertex_ES.vs", shaderText, 1024), (engine3D_shader_t*)shader);
	engine3D_shader_addFragmentShader(engine3D_resourceLoader_loadShader("basicFragment_ES.fs", shaderText, 1024), (engine3D_shader_t*)shader);
#endif
	engine3D_shader_compile((engine3D_shader_t*)shader);

	engine3D_shader_addUniform("transform", (engine3D_shader_t*)shader);
	engine3D_shader_addUniform("color", (engine3D_shader_t*)shader);
}

void engine3D_basicShader_updateUniforms(engine3D_basicShader_t * const shader, const engine3D_matrix4f_t *const worldMatrix, const engine3D_matrix4f_t *projectedMatrix, const engine3D_material_t *const material) {
	if (material->texture != NULL)
		engine3D_texture_bind(material->texture);
	else
		engine3D_renderUtil_unbindTextures();

	engine3D_shader_setUniformMat4f("transform", projectedMatrix, (engine3D_shader_t*)shader);
	engine3D_shader_setUniformVec3f("color", material->color, (engine3D_shader_t*)shader);
}