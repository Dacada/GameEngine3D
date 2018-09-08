#include <engine3D_window.h>

#include <stdbool.h>
#include <stdlib.h>

const int width = 800;
const int height = 600;
const char *const title = "3D Engine";

static void init(void) {
	engine3D_window_create(width, height, title);
}

static bool shouldClose(void) {
	return engine3D_window_closeRequested();
}

static void update(void) {
	engine3D_window_update();
}

static void cleanup(void) {
	engine3D_window_destroy();
}

int main(void) {
	init();
	while (!shouldClose()) {
		update();
	}
	cleanup();

	return EXIT_SUCCESS;
}