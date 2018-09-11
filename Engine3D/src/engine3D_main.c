#include <engine3D_main.h>
#include <engine3D_window.h>
#include <engine3D_game.h>
#include <engine3D_time.h>
#include <engine3D_input.h>

#include <stdio.h>
#include <stdbool.h>

const int engine3D_width = 800;
const int engine3D_height = 600;
const char *const engine3D_title = "3D Engine";
const double engine3D_frameCap = 5000.0;

static bool isRunning = false;

static void cleanup(void) {
	engine3D_window_destroy();
}

static void render(void) {
	engine3D_game_render();
	engine3D_window_update();
}

static void run(void) {
	isRunning = true;

	int frames = 0;
	double frameCounter = 0;

	const double frameTime = 1.0 / engine3D_frameCap;

	double lastFrameTime = engine3D_timer_getTime();
	double unprocessedTime = 0;

	while (isRunning) {
		bool doRender = false;

		double currentFrameTime = engine3D_timer_getTime();
		double lastFrameElapsedTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		unprocessedTime += lastFrameElapsedTime / engine3D_timer_second;
		frameCounter += lastFrameElapsedTime;

		while (unprocessedTime > frameTime)
		{
			doRender = true;

			unprocessedTime -= frameTime;

			if (engine3D_window_closeRequested()) {
				engine3D_stop();
			}

			engine3D_timer_setDelta(frameTime);
			engine3d_input_update();

			engine3D_game_input();
			engine3D_game_update();

			if (frameCounter >= engine3D_timer_second) {
				printf("%d\n", frames);
				frames = 0;
				frameCounter = 0;
			}
		}

		if (doRender) {
			render();
			frames++;
		} else {
			engine3D_timer_sleep(0.001 * engine3D_timer_second);
		}
	}

	cleanup();
}

void engine3D_init(void) {
	engine3D_timer_init();
	engine3D_window_create(engine3D_width, engine3D_height, engine3D_title);
	engine3D_game_init();
}

void engine3D_start(void) {
	if (isRunning) {
		return;
	}
	run();
}

void engine3D_stop(void) {
	isRunning = false;
}