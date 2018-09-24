#include <engine3D_texture.h>

void engine3D_texture_bind(engine3D_texture_t *const texture) {
	glBindTexture(GL_TEXTURE_2D, texture->id);
}
