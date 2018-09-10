#include <engine3D_vector.h>

#include <Windows.h>

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