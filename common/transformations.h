#ifndef OPENGLABS_TRANSFORMATIONS_H
#define OPENGLABS_TRANSFORMATIONS_H

#include "common.h"

static mat4 scaleMatrix(vec4 scale) {
    return {
            scale.x, 0.0, 0.0, 0.0,
            0.0, scale.y, 0.0, 0.0,
            0.0, 0.0, scale.z, 0.0,
            0.0, 0.0, 0.0, scale.w
    };
}

static mat4 rotationYMatrix(float angle) {
    return {
            cos(angle), 0.0, sin(angle), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(angle), 0.0, cos(angle), 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}

static mat4 offsetMatrix(vec3 position) {
    return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            position.x, position.y, position.z, 1.0f,
    };
}

static mat4 offsetMatrix(vec4 position) {
    return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            position.x, position.y, position.z, 1.0f,
    };
}

#endif //OPENGLABS_TRANSFORMATIONS_H
