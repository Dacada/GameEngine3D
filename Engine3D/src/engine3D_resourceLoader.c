#include <engine3D_resourceLoader.h>
#include <engine3D_util.h>
#include <engine3D_mesh.h>
#include <engine3D_vertex.h>

#include <FreeImage.h>

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

static void readFaces(char *input, int faces[3][3], size_t iv, size_t itv, size_t inv) {
	size_t i, j;

	for (i = 0; i < 9; i++) {
		faces[i / 3][i % 3] = -1;
	}

	while (isspace(*input)) input++;

	i = j = 0;
	while (*input != '\0') {
		if (isspace(*input)) {
			j++;
			i = 0;
			while (isspace(*input)) input++;
		}
		else if (*input == '/') {
			i++;
			input++;
		}
		else {
			long n = readNextLong(&input);

			size_t lastIndex;
			if (i == 0) {
				lastIndex = iv;
			}
			else if (i == 1) {
				lastIndex = itv;
			}
			else if (i == 2) {
				lastIndex = inv;
			}
			else {
				engine3D_util_bail("attempt to load invalid .obj file (too many items in face tuple)");
			}

			if (n > 0) {
				n -= 1;
			}
			else if (n < 0) {
				n = lastIndex - (n + 1);
			}
			else {
				engine3D_util_bail("attempt to load invalid .obj file (invalid index: 0)");
			}

			if (n > INT_MAX) engine3D_util_bail("attempt to load invalid .obj file (index too positive)");
			if (n < 0) engine3D_util_bail("attempt to load invalid .obj file (index too negative)");

			faces[j][i] = (int)n;
		}
	}
}

// indices is an array of arrays of structs used as the underlying data of a hash map that maps a face tuple (vertex, texture coord, normal) to an index
// struct fields meaning: the first three are the tuple, the index field is the index this tupple is mapped to, the last field is a pointer to the next
// it's an array of arrays because there might be hash collisions
struct bucket { int faceV; int faceT; int faceN; size_t index; struct bucket *next; };
struct bucket *indices[0x1000];
size_t lastIndex;

size_t getFaceKey(int face[3]) {
	size_t result = 0;

	for (int i = 0; i < 3; i++) {
		result += face[i];
		result %= 0x1000;
		result *= 5113;
		result %= 0x1000;
	}

	return result;
}

void initSeenIndex() {
	for (int i = 0; i < 0x1000; i++) {
		if (indices[i] != NULL) {
			struct bucket *b = indices[i];
			struct bucket *next;
			while (b != NULL) {
				next = b->next;
				free(b);
				b = next;
			}
		}
		indices[i] = NULL;
	}
	lastIndex = 0;
}

bool getSeenIndex(int face[3], size_t *seenIndex) {
	size_t key = getFaceKey(face);
	struct bucket *b = indices[key];
	if (b == NULL) {
		return false;
	}
	else {
		while ((b = b->next) != NULL) {
			if (b->faceV == face[0] && b->faceT == face[1] && b->faceN == face[2]) {
				*seenIndex = b->index;
				return true;
			}
		}
		return false;
	}
}

size_t setSeenIndex(int face[3]) {
	size_t key = getFaceKey(face);
	struct bucket *b = indices[key];

	if (b == NULL) {
		b = indices[key] = engine3D_util_safeMalloc(sizeof(struct bucket));
	}
	else {
		struct bucket *next = b->next;
		while (next != NULL) {
			b = next;
			next = b->next;
		}
	}

	b->faceV = face[0];
	b->faceT = face[1];
	b->faceN = face[2];
	b->index = lastIndex;
	b->next = NULL;
	return lastIndex++;
}

void engine3D_resourceLoader_loadMesh(const char *const filename, engine3D_mesh_t *const mesh) {
	char filepath[256] = ENGINE3D_RES_PATH "models/";
	strncat(filepath, filename, 128);

	initSeenIndex();

	size_t verticesCapacity = 4, indicesCapacity = 4;
	size_t verticesIndex = 0, indicesIndex = 0;
	engine3D_vertex_t *vertices = engine3D_util_safeMalloc(sizeof(engine3D_vertex_t) * verticesCapacity);
	unsigned int *indices = engine3D_util_safeMalloc(sizeof(unsigned int) * indicesCapacity);

	size_t vsCapacity = 4, vtsCapacity = 4, vnsCapacity = 4;
	size_t vsIndex = 0, vtsIndex = 0, vnsIndex = 0;
	engine3D_vector3f_t *vs = engine3D_util_safeMalloc(sizeof(engine3D_vector3f_t) * vsCapacity);
	engine3D_vector2f_t *vts = engine3D_util_safeMalloc(sizeof(engine3D_vector2f_t) * vsCapacity);
	engine3D_vector3f_t *vns = engine3D_util_safeMalloc(sizeof(engine3D_vector3f_t) * vsCapacity);

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
			engine3D_util_bail("attempt to load invalid .obj file (invalid token)");
		}

		if (strncmp(token, "#", 2) == 0 || strncmp(token, "\n", 2) == 0) {
			continue;
		}
		else if (strncmp(token, "v", 2) == 0) {
			float coords[3];
			coords[0] = readNextFloat(&current);
			coords[1] = readNextFloat(&current);
			coords[2] = readNextFloat(&current);
			while (!isspace(*current) && *current != '\0') current++;
			if (*current != '\0')
				engine3D_util_errPrintf("reading .obj file: ignoring optional w element of vertex", token);

			if (vsIndex >= vsCapacity) {
				vsCapacity *= 2;
				vs = engine3D_util_safeRealloc(vs, sizeof(engine3D_vector3f_t) * vsCapacity);
			}
			vs[vsIndex].x = coords[0];
			vs[vsIndex].y = coords[1];
			vs[vsIndex].z = coords[2];
			vsIndex++;
		}
		else if (strncmp(token, "vt", 3) == 0) {
			float coords[2];
			coords[0] = readNextFloat(&current);
			coords[1] = readNextFloat(&current);
			while (!isspace(*current) && *current != '\0') current++;
			if (*current != '\0')
				engine3D_util_errPrintf("reading .obj file: ignoring optional w element of texture", token);

			if (vtsIndex >= vtsCapacity) {
				vtsCapacity *= 2;
				vts = engine3D_util_safeRealloc(vts, sizeof(engine3D_vector2f_t) * vtsCapacity);
			}
			vts[vtsIndex].x = coords[0];
			vts[vtsIndex].y = coords[1];
			vtsIndex++;
		}
		else if (strncmp(token, "vn", 3) == 0) {
			float coords[3];
			coords[0] = readNextFloat(&current);
			coords[1] = readNextFloat(&current);
			coords[2] = readNextFloat(&current);

			if (vnsIndex >= vnsCapacity) {
				vnsCapacity *= 2;
				vns = engine3D_util_safeRealloc(vns, sizeof(engine3D_vertex_t) * vnsCapacity);
			}
			vns[vnsIndex].x = coords[0];
			vns[vnsIndex].y = coords[1];
			vns[vnsIndex].z = coords[2];
			vnsIndex++;
		}
		else if (strncmp(token, "f", 2) == 0) {
			int faces[3][3];
			readFaces(current, faces, vsIndex, vtsIndex, vnsIndex);

			if (indicesIndex + 2 >= indicesCapacity) {
				while (indicesIndex + 2 >= indicesCapacity) {
					indicesCapacity *= 2;
				}
				indices = engine3D_util_safeRealloc(indices, sizeof(unsigned int) * indicesCapacity);
			}

			for (int i = 0; i < 3; i++)
			{
				size_t seenIndex;
				bool hasBeenSeen = getSeenIndex(faces[i], &seenIndex);
				if (!hasBeenSeen) {
					seenIndex = setSeenIndex(faces[i]);

					if (verticesIndex + 1 >= verticesCapacity) {
						verticesCapacity *= 2;
						vertices = engine3D_util_safeRealloc(vertices, sizeof(engine3D_vertex_t) * verticesCapacity);
					}

					vertices[verticesIndex].vec.x = vs[faces[i][0]].x;
					vertices[verticesIndex].vec.y = vs[faces[i][0]].y;
					vertices[verticesIndex].vec.z = vs[faces[i][0]].z;
					if (faces[i][1] >= 0) {
						vertices[verticesIndex].texCoord.x = vts[faces[i][1]].x;
						vertices[verticesIndex].texCoord.y = vts[faces[i][1]].y;
					}
					if (faces[i][2] >= 0) {
						vertices[verticesIndex].normal.x = vns[faces[i][2]].x;
						vertices[verticesIndex].normal.y = vns[faces[i][2]].y;
						vertices[verticesIndex].normal.z = vns[faces[i][2]].z;
					}

					verticesIndex++;
				}

				indices[indicesIndex++] = seenIndex;
			}
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
	engine3D_mesh_addVertices(mesh, vertices, verticesIndex, indices, indicesIndex, true);

	free(vs);
	free(vts);
	free(vns);
	free(vertices);
	free(indices);
}

void engine3D_resourceLoader_loadTexture(const char *const filename, engine3D_texture_t *const texture) {
	char filepath[256] = ENGINE3D_RES_PATH "textures/";
	strncat(filepath, filename, 128);

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = NULL;
	BYTE* bits;
	unsigned int width, height;

	fif = FreeImage_GetFileType(filepath, 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filepath);
	if (fif == FIF_UNKNOWN)
		engine3D_util_bail("attempt to load texture of unknown image type");

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filepath, 0);

	if (!dib)
		engine3D_util_bail("failed to load image for texture");

	FIBITMAP *dib32 = FreeImage_ConvertTo32Bits(dib);
	FreeImage_Unload(dib);

	bits = FreeImage_GetBits(dib32);
	width = FreeImage_GetWidth(dib32);
	height = FreeImage_GetHeight(dib32);
	if (bits == 0 || width == 0 || height == 0)
		engine3D_util_bail("failed to load image data for texture");

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);

	FreeImage_Unload(dib32);
}
