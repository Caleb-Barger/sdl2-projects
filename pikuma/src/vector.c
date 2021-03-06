#include "vector.h"

vec3_t vec3_rotate_x(vec3_t vec, float a) {

    vec3_t rotated_vec = {
        .x = vec.x,
        .y = vec.y*sin(a) + vec.z*cos(a),
        .z = vec.y*cos(a) - vec.z*sin(a)
    };

    return rotated_vec;
}

vec3_t vec3_rotate_y(vec3_t vec, float a) {

    vec3_t rotated_vec = {
        .x = vec.x*cos(a) - vec.z*sin(a),
        .y = vec.y,
        .z = vec.x*sin(a) + vec.z*cos(a)
    };

    return rotated_vec;
}

vec3_t vec3_rotate_z(vec3_t vec, float a) {

    vec3_t rotated_vec = {
        .x = vec.x*cos(a) - vec.y*sin(a),
        .y = vec.x*sin(a) + vec.y*cos(a),
        .z = vec.z
    };
    
    return rotated_vec;
}
