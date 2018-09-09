#pragma once

#include <stdio.h>

typedef struct vector2d_t {
	double x, y;
} vector2d_t;

int fprintf_vector2d(FILE *stream, vector2d_t *v);