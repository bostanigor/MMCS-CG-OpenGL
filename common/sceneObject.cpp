#include "sceneObject.h"

void sceneObject::render() {
    glBindVertexArray(model->VAO);
    glDrawArrays(GL_TRIANGLES, 0, model->elementCount);
    glBindVertexArray(0);
}

sceneObject::sceneObject(model3D * model, Material material, vec3 position, float angle) {
    this->model = model;
    this->material = material;
    this->position = position;
    this->angle = angle;
}

mat4 sceneObject::getModelTransform() {
    mat4 rotation = {1.0, 0.0, 0.0, 0.0,
                     0.0, cos(angle), -sin(angle), 0.0,
                     0.0, sin(angle), cos(angle), 0.0,
                     0.0, 0.0, 0.0, 1.0};
    mat4 pos = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        position.x, position.y, position.z, 1.0,
    };

    return rotation * pos;
}
