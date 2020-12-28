#ifndef OPENGLABS_SCENEOBJECT_H
#define OPENGLABS_SCENEOBJECT_H

#include "model3D.h"

class sceneObject {
    model3D * model;

    GLuint texture;
    Material material;

    vec3 position;

public:
    sceneObject() {};
    sceneObject(model3D * model, GLuint texture, Material material);

    void render();
};



#endif //OPENGLABS_SCENEOBJECT_H
