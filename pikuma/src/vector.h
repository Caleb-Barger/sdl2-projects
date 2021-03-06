#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

vec3_t vec3_rotate_x(vec3_t, float);
vec3_t vec3_rotate_y(vec3_t, float);
vec3_t vec3_rotate_z(vec3_t, float);

#endif
