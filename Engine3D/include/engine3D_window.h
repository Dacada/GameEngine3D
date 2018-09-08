#pragma once

#include <stdbool.h>

// Create the window. Bail on error.
void engine3D_window_create(const int width, const int height, const char *const title);

// Poll events and perform the framebuffer swap.
// If on debug mode, query for OpenGL errors.
void engine3D_window_update();

// True if window must be closed.
bool engine3D_window_closeRequested();

// Set the ints which pointers are given to the window's current width and height.
// NULL is an accepted value for any of the two pointers.
void engine3D_window_getSize(int *const width, int *const height);

const char *const engine3D_window_getTitle();

// Terminate and destroy the window.
void engine3D_window_destroy();
