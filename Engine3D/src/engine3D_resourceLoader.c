#include <engine3D_resourceLoader.h>
#include <engine3D_util.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

char *engine3D_resourceLoader_loadShader(const char *const filename, char *const text, size_t size) {
	char filepath[256] = ENGINE3D_RES_PATH "shaders/";
	strncat(filepath, filename, 128);

	FILE *f = fopen(filepath, "r");
	if (f == NULL) {
		perror("fopen");
		engine3D_util_bail("failed to load shader");
	}

	size_t s = fread(text, sizeof(char), size, f);
	int err;
	if ((err = ferror(f)) != 0) {
		engine3D_util_errPrintf("fprintf: error %d", err);
		engine3D_util_bail("failed to load shader");
	}
	text[s] = '\0'; // Ensure it's null terminated

	return text;
}
