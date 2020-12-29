#ifndef OPENGLABS_SCENEOBJECT_H
#define OPENGLABS_SCENEOBJECT_H

#include "model3D.h"

class sceneObject {
    model3D * model;

public:
    Material material;
    vec4 position;
    vec4 scale;
    GLfloat angleY = 0.0f;

    sceneObject() {};
    sceneObject(model3D * model, Material material, vec4 position = { 0.0f, 0.0f, 0.0f, 1.0f }, vec4 scale = { 1.0, 1.0, 1.0, 1.0 });

    void rotateOY(GLfloat angle);
    mat4 getModelTransform();

    void render();
};

#endif //OPENGLABS_SCENEOBJECT_H
