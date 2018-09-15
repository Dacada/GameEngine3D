#include <engine3D_mesh.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

engine3D_mesh_t * engine3D_mesh_init(engine3D_mesh_t * const mesh) {
	glGenBuffers(1, &mesh->vbo);
	mesh->size = 0;
	return mesh;
}

engine3D_mesh_t * engine3D_mesh_addVertices(engine3D_mesh_t * const mesh, engine3D_vertex_t vertices[], size_t vertices_len) {
	mesh->size = vertices_len * sizeof(engine3D_vertex_t);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh->size, vertices, GL_STATIC_DRAW);
	return mesh;
}

void engine3D_mesh_draw(const engine3D_mesh_t * const mesh) {
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(engine3D_vertex_t), 0);

	glDrawArrays(GL_TRIANGLES, 0, mesh->size);

	glDisableVertexAttribArray(0);
}
