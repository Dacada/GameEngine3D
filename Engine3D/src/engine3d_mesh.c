#include <engine3D_mesh.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

engine3D_mesh_t * engine3D_mesh_init(engine3D_mesh_t * const mesh) {
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ibo);
	mesh->len_vbo = 0;
	mesh->len_ibo = 0;
	return mesh;
}

engine3D_mesh_t * engine3D_mesh_addVertices(engine3D_mesh_t * const mesh, engine3D_vertex_t vertices[], size_t vertices_len, unsigned int indices[], size_t indices_len) {
	mesh->len_vbo = vertices_len;
	mesh->len_ibo = indices_len;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_len * sizeof(engine3D_vertex_t), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_len * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	return mesh;
}

void engine3D_mesh_draw(const engine3D_mesh_t * const mesh) {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(engine3D_vertex_t), (void*)offsetof(engine3D_vertex_t, vec));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(engine3D_vertex_t), (void*)offsetof(engine3D_vertex_t, texCoord));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glDrawElements(GL_TRIANGLES, mesh->len_ibo, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
