#ifndef ENGINE3D_MESH_H
#define ENGINE3D_MESH_H

#include <engine3D_vertex.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

typedef struct engine3D_mesh_t {
	GLuint vbo;
	GLsizei size; //size in bytes of the underlying vertex array vbo refers to
} engine3D_mesh_t;

// Takes pointer to mesh struct, initializes it, returns same pointer
engine3D_mesh_t *engine3D_mesh_init(engine3D_mesh_t *const mesh);

// Create vbo for the vertices
engine3D_mesh_t *engine3D_mesh_addVertices(engine3D_mesh_t *const mesh, engine3D_vertex_t vertices[], size_t vertices_len);

void engine3D_mesh_draw(const engine3D_mesh_t *const mesh);

#endif /* ENGINE3D_MESH_H */
