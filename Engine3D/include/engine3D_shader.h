#ifndef ENGINE3D_SHADER_H
#define ENGINE3D_SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

typedef struct engine3D_shader_t {
	GLuint program;
} engine3D_shader_t;

engine3D_shader_t *engine3D_shader_init(engine3D_shader_t *const shader);

engine3D_shader_t *engine3D_shader_addVertexShader(const char *const text, engine3D_shader_t * const shader);

engine3D_shader_t *engine3D_shader_addGeometryShader(const char *const text, engine3D_shader_t * const shader);

engine3D_shader_t *engine3D_shader_addFragmentShader(const char *const text, engine3D_shader_t * const shader);

void engine3D_shader_compile(const engine3D_shader_t * const shader);

void engine3D_shader_bind(const engine3D_shader_t * const shader);

#endif
