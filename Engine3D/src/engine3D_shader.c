#include <engine3D_shader.h>
#include <engine3D_util.h>

#include <stdlib.h>

static void addProgram(const char *const text, engine3D_shader_t * const shader, GLenum type) {
	GLuint shaderId = glCreateShader(type);
	if (shader == 0) {
		engine3D_util_bail("shader creation failed");
	}

	glShaderSource(shaderId, 1, &text, NULL);
	glCompileShader(shaderId);

	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		char infoLog[1024];
		glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
		engine3D_util_errPrintf(infoLog);
		engine3D_util_bail("shader compilation failed");
	}

	glAttachShader(shader->program, shaderId);
}


engine3D_shader_t *engine3D_shader_init(engine3D_shader_t * const shader) {
	shader->program = glCreateProgram();
	if (shader->program == 0)
	{
		engine3D_util_bail("shader program creation failed");
	}
	return shader;
}

engine3D_shader_t *engine3D_shader_addVertexShader(const char *const text, engine3D_shader_t * const shader) {
	addProgram(text, shader, GL_VERTEX_SHADER);
	return shader;
}

engine3D_shader_t *engine3D_shader_addGeometryShader(const char *const text, engine3D_shader_t * const shader) {
	addProgram(text, shader, GL_GEOMETRY_SHADER);
	return shader;
}

engine3D_shader_t *engine3D_shader_addFragmentShader(const char *const text, engine3D_shader_t * const shader) {
	addProgram(text, shader, GL_FRAGMENT_SHADER);
	return shader;
}

void engine3D_shader_compile(const engine3D_shader_t * const shader) {
	glLinkProgram(shader->program);

	GLint status;
	glGetShaderiv(shader->program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		char infoLog[1024];
		glGetShaderInfoLog(shader->program, 1024, NULL, infoLog);
		engine3D_util_errPrintf(infoLog);
		engine3D_util_bail("shader linking failed");
	}

	glValidateProgram(shader->program);
}

void engine3D_shader_bind(const engine3D_shader_t * const shader) {
	glUseProgram(shader->program);
}
