#include <engine3D_vector.h>

int fprintf_vector2d(FILE * stream, vector2d_t * v) {
	return fprintf(stream, "vector2d<%f,%f>", v->x, v->y);
}
