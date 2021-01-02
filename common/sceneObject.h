#ifndef OPENGLABS_SCENEOBJECT_H
#define OPENGLABS_SCENEOBJECT_H

#include "model3D.h"

class sceneObject {
    model3D * model;

public:
    Material material;
    vec3 position;
    float angle;

    sceneObject() {};
    sceneObject(model3D * model, Material material, vec3 position = { 0.0f, 0.0f, 0.0f }, float angle = 0.0);

    mat4 getModelTransform();

    void render();
};

#endif //OPENGLABS_SCENEOBJECT_H
