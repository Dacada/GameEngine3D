#include "..\include\engine3D_time.h"
#pragma once

#ifdef _WIN32
#include <Windows.h>

const double engine3D_timer_second = 1;

static double frequency;
static LARGE_INTEGER start;

void engine3D_timer_init(void) {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	frequency = 1.0 / freq.QuadPart;
	QueryPerformanceCounter(&start);
}

double engine3D_timer_getTime(void) {
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);
	LONGLONG cycles = current.QuadPart - start.QuadPart;
	return cycles * frequency;
}

void engine3D_timer_sleep(const double t) {
	Sleep((DWORD)(t * 1000.0));
}
#endif

// TODO: Linux compatibility
#ifdef __unix__
const double engine3D_timer_second = 0;

void engine3D_timer_init(void) {
}

double engine3D_timer_getTime(void) {
	return 0;
}

void engine3D_timer_sleep(const double t) {
}
#endif

// TODO: Mac compatibility
#if defined(__APPLE__) && defined(__MACH__)
const double engine3D_timer_second = 0;

void engine3D_timer_init(void) {
}

double engine3D_timer_getTime(void) {
	return 0;
}

void engine3D_timer_sleep(const double t) {
}
#endif

static double delta;

double engine3D_timer_getDelta(void) {
	return delta;
}

void engine3D_timer_setDelta(const double d) {
	delta = d;
}
