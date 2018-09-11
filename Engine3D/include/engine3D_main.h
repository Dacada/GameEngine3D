#ifndef ENGINE3D_MAIN_H
#define ENGINE3D_MAIN_H

extern const int engine3D_width;
extern const int engine3D_height;
extern const char *const engine3D_title;
extern const double engine3D_frameCap;

void engine3D_init(void);

void engine3D_start(void);

void engine3D_stop(void);

#endif /* ENGINE3D_MAIN_H */