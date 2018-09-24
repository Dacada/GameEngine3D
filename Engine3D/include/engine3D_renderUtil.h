#ifndef ENGINE3D_RENDERUTIL_H
#define ENGINE3D_RENDERUTIL_H

#include <stdbool.h>

void engine3D_renderUtil_clearScreen(void);

void engine3D_renderUtil_setTextures(bool enabled);

void engine3D_renderUtil_initGraphics(void);

const char *engine3D_renderUtil_getOpenGLVersion(void);

#endif /* ENGINE3D_RENDERUTIL_H */