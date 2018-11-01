#ifndef ENGINE3D_UTIL_H
#define ENGINE3D_UTIL_H

#include <GL/glew.h>

#include <stdlib.h>

#ifdef _MSC_VER
__declspec(noreturn) void engine3D_util_bail(const char *const message);
__declspec(noreturn) void engine3D_util_quit(const char *const message);
#elif __GNUC__
void engine3D_util_bail(const char *const message) __attribute__((noreturn));
void engine3D_util_quit(const char *const message) __attribute__((noreturn));
#else
void engine3D_util_bail(const char *const message);
void engine3D_util_quit(const char *const message);
#endif

void engine3D_util_reportGlError(void);

#ifdef __GNUC__
int engine3D_util_errPrintf(const char *format, ...) __attribute__((format(printf, 1, 2)));;
#else
int engine3D_util_errPrintf(const char *format, ...);
#endif

#ifdef __GNUC__
void *engine3D_util_safeMalloc(size_t size) __attribute__((malloc, alloc_size(1)));
void *engine3D_util_safeCalloc(size_t nmemb, size_t size) __attribute__((malloc, alloc_size(1, 2)));
void *engine3D_util_safeRealloc(void *ptr, size_t size) __attribute__((alloc_size(2)));
#else
void *engine3D_util_safeMalloc(size_t size);
void *engine3D_util_safeCalloc(size_t nmemb, size_t size);
void *engine3D_util_safeRealloc(void *ptr, size_t size);
#endif

#endif /* ENGINE3D_UTIL_H */
