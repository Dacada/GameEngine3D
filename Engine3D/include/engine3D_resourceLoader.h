#ifndef ENGINE3D_RESOURCELOADER_H
#define ENGINE3D_RESOURCELOADER_H

#include <engine3d_mesh.h>

#include <stdlib.h>

char *engine3D_resourceLoader_loadShader(const char *const filename, char *const text, size_t size);

void engine3D_resourceLoader_loadMesh(const char *const filename, engine3D_mesh_t *mesh);

#endif /* ENGINE3D_RESOURCELOADER_H */