#ifndef ENGINE3D_TRANSFORM_H
#define ENGINE3D_TRANSFORM_H

#include <engine3D_vector.h>

typedef struct engine3D_transform_t {
	engine3D_vector3f_t translation;
} engine3D_transform_t;

void engine3D_transform_init(engine3D_transform_t *const transform);

void engine3D_transform_getTransformation(const engine3D_transform_t *const transform, engine3D_matrix4f_t *const transformation);

#endif /* ENGINE3D_TRANSFORM_H */