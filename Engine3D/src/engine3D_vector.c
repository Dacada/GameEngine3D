#include <engine3D_vector.h>

#include <math.h>

float engine3D_vector2f_length(const engine3D_vector2f_t * const v) {
	return sqrtf(v->x * v->x + v->y * v->y);
}

float engine3D_vector2f_dot(const engine3D_vector2f_t * const v1, const engine3D_vector2f_t * const v2) {
	return v1->x * v2->x + v1->y * v2->y;
}

engine3D_vector2f_t * engine3D_vector2f_normalize(engine3D_vector2f_t * const v) {
	float length = engine3D_vector2f_length(v);
	v->x /= length;
	v->y /= length;
	return v;
}

engine3D_vector2f_t * engine3D_vector2f_rotateRad(const engine3D_vector2f_t * const v, float angle, engine3D_vector2f_t *const result) {
	float c = cosf(angle);
	float s = sinf(angle);

	result->x = v->x * c - v->y * s;
	result->y = v->x * s + v->y * c;

	return result;
}

engine3D_vector2f_t * engine3D_vector2f_rotateDeg(const engine3D_vector2f_t * const v, float angle, engine3D_vector2f_t *const result) {
	float rad = angle / 180 * (float)M_PI;
	return engine3D_vector2f_rotateRad(v, rad, result);
}

engine3D_vector2f_t * engine3D_vector2f_add(const engine3D_vector2f_t * const v1, const engine3D_vector2f_t * const v2, engine3D_vector2f_t * const result) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	return result;
}

engine3D_vector2f_t * engine3D_vector2f_addf(const engine3D_vector2f_t * const v, float f, engine3D_vector2f_t * const result) {
	result->x = v->x + f;
	result->y = v->y + f;
	return result;
}

engine3D_vector2f_t * engine3D_vector2f_sub(const engine3D_vector2f_t * const v1, const engine3D_vector2f_t * const v2, engine3D_vector2f_t * const result) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	return result;
}

engine3D_vector2f_t * engine3D_vector2f_subf(const engine3D_vector2f_t * const v, float f, engine3D_vector2f_t * const result) {
	result->x = v->x - f;
	result->y = v->y - f;
	return result;
}

engine3D_vector2f_t * engine3D_vector2f_mul(const engine3D_vector2f_t * const v1, const engine3D_vector2f_t * const v2, engine3D_vector2f_t * const result) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	return result;
}

engine3D_vector2f_t * engine3D_vector2f_mulf(const engine3D_vector2f_t * const v, float f, engine3D_vector2f_t * const result) {
	result->x = v->x * f;
	result->y = v->y * f;
	return result;
}

engine3D_vector2f_t * engine3D_vector2f_div(const engine3D_vector2f_t * const v1, const engine3D_vector2f_t * const v2, engine3D_vector2f_t * const result) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
	return result;
}

engine3D_vector2f_t * engine3D_vector2f_divf(const engine3D_vector2f_t * const v, float f, engine3D_vector2f_t * const result) {
	result->x = v->x / f;
	result->y = v->y / f;
	return result;
}

int engine3D_vector2f_fprintf(FILE *stream, const engine3D_vector2f_t *const v) {
	return fprintf(stream, "vector2d<%f,%f>", v->x, v->y);
}



float engine3D_vector3f_length(const engine3D_vector3f_t * const v) {
	return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

float engine3D_vector3f_dot(const engine3D_vector3f_t * const v1, const engine3D_vector3f_t * const v2) {
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

engine3D_vector3f_t *engine3D_vector3f_cross(const engine3D_vector3f_t * const v1, const engine3D_vector3f_t * const v2, engine3D_vector3f_t * const result) {
	result->x = v1->y * v2->z - v1->z * v2->y;
	result->y = v1->z * v2->x - v1->x * v2->z;
	result->z = v1->x * v2->y - v1->y * v2->x;

	return result;
}

engine3D_vector3f_t * engine3D_vector3f_normalize(engine3D_vector3f_t * const v) {
	float length = engine3D_vector3f_length(v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
	return v;
}

engine3D_vector3f_t * engine3D_vector3f_rotateRad(const engine3D_vector3f_t * const v, float angle, engine3D_vector3f_t *const result) {
	// Suppress unused warnings
	(void)(v);
	(void)(angle);

	return result;
}

engine3D_vector3f_t * engine3D_vector3f_rotateDeg(const engine3D_vector3f_t * const v, float angle, engine3D_vector3f_t *const result)
{
	float rad = angle / 180 * (float)M_PI;
	return engine3D_vector3f_rotateRad(v, rad, result);
}

engine3D_vector3f_t * engine3D_vector3f_add(const engine3D_vector3f_t * const v1, const engine3D_vector3f_t * const v2, engine3D_vector3f_t * const result) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
	return result;
}

engine3D_vector3f_t * engine3D_vector3f_addf(const engine3D_vector3f_t * const v, float f, engine3D_vector3f_t * const result) {
	result->x = v->x + f;
	result->y = v->y + f;
	result->z = v->z + f;
	return result;
}

engine3D_vector3f_t * engine3D_vector3f_sub(const engine3D_vector3f_t * const v1, const engine3D_vector3f_t * const v2, engine3D_vector3f_t * const result) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
	return result;
}

engine3D_vector3f_t * engine3D_vector3f_subf(const engine3D_vector3f_t * const v, float f, engine3D_vector3f_t * const result) {
	result->x = v->x - f;
	result->y = v->y - f;
	result->z = v->z - f;
	return result;
}

engine3D_vector3f_t * engine3D_vector3f_mul(const engine3D_vector3f_t * const v1, const engine3D_vector3f_t * const v2, engine3D_vector3f_t * const result) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	result->z = v1->z * v2->z;
	return result;
}

engine3D_vector3f_t * engine3D_vector3f_mulf(const engine3D_vector3f_t * const v, float f, engine3D_vector3f_t * const result) {
	result->x = v->x * f;
	result->y = v->y * f;
	result->z = v->z * f;
	return result;
}

engine3D_vector3f_t * engine3D_vector3f_div(const engine3D_vector3f_t * const v1, const engine3D_vector3f_t * const v2, engine3D_vector3f_t * const result) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
	result->z = v1->z / v2->z;
	return result;
}

engine3D_vector3f_t * engine3D_vector3f_divf(const engine3D_vector3f_t * const v, float f, engine3D_vector3f_t * const result) {
	result->x = v->x / f;
	result->y = v->y / f;
	result->z = v->z / f;
	return result;
}

int engine3D_vector3f_fprintf(FILE * stream, const engine3D_vector3f_t *const v) {
	return fprintf(stream, "vector2d<%f,%f,%f>", v->x, v->y, v->z);
}



void engine3D_matrix4f_setIdentity(engine3D_matrix4f_t * const matrix) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			matrix->mat[i][j] = 0;
		}
		matrix->mat[i][i] = 1;
	}
}

void engine3D_matrix4f_setTranslation(engine3D_matrix4f_t * const matrix, float x, float y, float z) {
	engine3D_matrix4f_setIdentity(matrix);
	matrix->mat[0][3] = x;
	matrix->mat[1][3] = y;
	matrix->mat[2][3] = z;
}

void engine3D_matrix4f_mul(const engine3D_matrix4f_t * const m1, const engine3D_matrix4f_t * const m2, engine3D_matrix4f_t * const r) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			float sum = 0;
			for (size_t k = 0; k < 4; k++) {
				sum += m1->mat[i][k] * m2->mat[k][j];
			}
			r->mat[i][j] = sum;
		}
	}
}



float engine3D_quaternion_length(const engine3D_quaternion_t * const v) {
	return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
}

engine3D_quaternion_t * engine3D_quaternion_normalize(engine3D_quaternion_t * const v) {
	float length = engine3D_quaternion_length(v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
	v->w /= length;
	return v;
}

engine3D_quaternion_t * engine3D_quaternion_conjugate(const engine3D_quaternion_t * const v, engine3D_quaternion_t * const r) {
	r->x = -v->x;
	r->y = -v->y;
	r->z = -v->z;
	r->w = v->w;
	return r;
}

engine3D_quaternion_t * engine3D_quaternion_mul(const engine3D_quaternion_t * const v1, const engine3D_quaternion_t * const v2, engine3D_quaternion_t * const r) {
	r->w = v1->w * v2->w - v1->x * v2->x - v1->y * v2->y - v1->z * v2->z;
	r->x = v1->x * v2->w + v1->w * v2->x + v1->y * v2->z - v1->z * v2->y;
	r->y = v1->y * v2->w + v1->w * v2->y + v1->z * v2->x - v1->x * v2->z;
	r->z = v1->z * v2->w + v1->w * v2->z + v1->x * v2->y - v1->y * v2->x;
	return r;
}

engine3D_quaternion_t * engine3D_quaternion_mulv(const engine3D_quaternion_t * const v1, const engine3D_vector3f_t * const v2, engine3D_quaternion_t * const r) {
	r->w = -v1->x * v2->x - v1->y * v2->y - v1->z * v2->z;
	r->x =  v1->w * v2->x + v1->y * v2->z - v1->z * v2->y;
	r->y =  v1->w * v2->y + v1->z * v2->x - v1->x * v2->z;
	r->z =  v1->w * v2->z + v1->x * v2->y - v1->y * v2->x;
	return r;
}
