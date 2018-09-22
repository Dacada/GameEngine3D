#include <engine3D_resourceLoader.h>
#include <engine3D_util.h>
#include <engine3D_mesh.h>
#include <engine3D_vertex.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

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
		engine3D_util_errPrintf("fread: error %d", err);
		engine3D_util_bail("failed to load shader");
	}
	text[s] = '\0'; // Ensure it's null terminated

	fclose(f);

	return text;
}

// Read one line from stream. If line is greater than maxSize return -2.
// If error is found on stream or eof, return -1
// Otherwise return 0;
static int readLine(FILE *stream, char buff[], size_t maxSize) {
	if (ferror(stream) || feof(stream)) {
		return -1;
	}

	if (fgets(buff, maxSize, stream) == NULL) {
		return -1;
	}

	char *ptr = strchr(buff, '\n');
	if (ptr != NULL) {
		*ptr = '\0';
		return 0;
	}
	else {
		if (feof(stream))
			return -1;
		else
			return -2;
	}
}

static void skipWhitespace(char **buff) {
	char *b = *buff;
	while (*b != '\0' && isspace(*b) != 0) {
		b++;
	}
	*buff = b;
}

static char *getNextToken(char *ptr, char buff[], size_t len) {
	skipWhitespace(&ptr);

	if (*ptr == '\0') {
		buff[0] = '\n';
		buff[1] = '\0';
		return ptr;
	}

	for (size_t i = 0; i < len; i++) {
		if (isspace(*ptr)) {
			buff[i] = '\0';
			return ptr;
		}

		buff[i] = *ptr;
		ptr++;
	}

	return NULL;
}

static float readNextFloat(char **ptr) {
	char *tmp;
	errno = 0;
	float num = strtof(*ptr, &tmp);

	if (errno != 0) {
		perror("strtof");
		engine3D_util_bail("attempt to load invalid .obj file (error reading float)");
	}

	if (*ptr == tmp) {
		engine3D_util_bail("attempt to load invalid .obj file (could not find float)");
	}

	*ptr = tmp;
	return num;
}

static long readNextLong(char **ptr) {
	char *tmp;
	errno = 0;
	long num = strtol(*ptr, &tmp, 10);

	if (errno != 0) {
		perror("strtol");
		engine3D_util_bail("attempt to load invalid .obj file (error reading long)");
	}

	if (*ptr == tmp) {
		engine3D_util_bail("attempt to load invalid .obj file (could not find long)");
	}

	*ptr = tmp;

	return num;
}

static unsigned int normalizeToUInt(long input, size_t lastIndex) {
	long num;

	if (input > 0) {
		num = input - 1;
	}
	else if (input < 0) {
		num = lastIndex - (input + 1);
	}
	else {
		engine3D_util_bail("attempt to load invalid .obj file (invalid index: 0)");
	}

	if (num > UINT_MAX) {
		engine3D_util_bail("attempt to load invalid .obj file (index too positive)");
	}
	if (num < 0) {
		engine3D_util_bail("attempt to load invalid .obj file (index too negative)");
	}

	return (unsigned int)num;
}

void engine3D_resourceLoader_loadMesh(const char *const filename, engine3D_mesh_t *const mesh) {
	char filepath[256] = ENGINE3D_RES_PATH "models/";
	strncat(filepath, filename, 128);

	size_t verticesCapacity = 4, indicesCapacity = 4;
	size_t verticesIndex = 0, indicesIndex = 0;
	engine3D_vertex_t *vertices = engine3D_util_safeMalloc(sizeof(engine3D_vertex_t) * verticesCapacity);
	unsigned int *indices = engine3D_util_safeMalloc(sizeof(unsigned int) * indicesCapacity);

	size_t filenameLen = strlen(filepath);
	if (filenameLen < 4 || strncmp(filepath + filenameLen - 4, ".obj", 4) != 0) {
		engine3D_util_bail("attempt to load unsupported mesh file format (file name doesn't end with '.obj'");
	}

	FILE *f = fopen(filepath, "r");
	if (f == NULL) {
		perror("fopen");
		engine3D_util_bail("failed to load mesh file");
	}

	int ret;
	char lineBuff[1024];
	while ((ret = readLine(f, lineBuff, 1024)) == 0) {
		char *current = lineBuff;
		char token[256];

		current = getNextToken(current, token, 256);
		if (current == NULL) {
			engine3D_util_bail("attempt to load invalid .obj file (unrecognized token)");
		}

		if (strncmp(token, "#", 2) == 0 || strncmp(token, "\n", 2) == 0)
			continue;

		if (strncmp(token, "v", 2) == 0) {
			float coords[4];
			coords[0] = readNextFloat(&current);
			coords[1] = readNextFloat(&current);
			coords[2] = readNextFloat(&current);

			if (verticesIndex >= verticesCapacity) {
				while (verticesIndex >= verticesCapacity) {
					verticesCapacity *= 2;
				}
				vertices = engine3D_util_safeRealloc(vertices, sizeof(engine3D_vertex_t) * verticesCapacity);
			}
			vertices[verticesIndex].vec.x = coords[0];
			vertices[verticesIndex].vec.y = coords[1];
			vertices[verticesIndex].vec.z = coords[2];
			verticesIndex++;
		}
		else if (strncmp(token, "f", 2) == 0) {
			unsigned int faces[3];
			faces[0] = normalizeToUInt(readNextLong(&current), verticesIndex);
			while (!isspace(*current) && *current != '\0') current++;
			faces[1] = normalizeToUInt(readNextLong(&current), verticesIndex);
			while (!isspace(*current) && *current != '\0') current++;
			faces[2] = normalizeToUInt(readNextLong(&current), verticesIndex);

			if (indicesIndex + 2 >= indicesCapacity) {
				while (indicesIndex + 2 >= indicesCapacity) {
					indicesCapacity *= 2;
				}
				indices = engine3D_util_safeRealloc(indices, sizeof(unsigned int) * indicesCapacity);
			}
			indices[indicesIndex++] = faces[0];
			indices[indicesIndex++] = faces[1];
			indices[indicesIndex++] = faces[2];
		}
		else {
			engine3D_util_errPrintf("reading .obj file: ignoring token: %s", token);
		}
	}

	if (ret == -2) {
		engine3D_util_bail("attempt to load invalid .obj file (file's lines detected as too long)");
	}
	else {
		int err = ferror(f);
		if (err != 0) {
			engine3D_util_errPrintf("reading file: error %d", err);
			engine3D_util_bail("failed to load mesh file");
		}
	}

	fclose(f);

	engine3D_mesh_init(mesh);
	engine3D_mesh_addVertices(mesh, vertices, verticesIndex, indices, indicesIndex);

	free(vertices);
	free(indices);
}
