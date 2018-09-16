#include <engine3D_transform.h>

void engine3D_transform_init(engine3D_transform_t *const transform) {
	transform->translation.x = 0;
	transform->translation.y = 0;
	transform->translation.z = 0;
}

void engine3D_transform_getTransformation(const engine3D_transform_t *const transform, engine3D_matrix4f_t * const transformation) {
	engine3D_matrix4f_setTranslation(transformation, transform->translation.x, transform->translation.y, transform->translation.z);
	return transformation;
}
