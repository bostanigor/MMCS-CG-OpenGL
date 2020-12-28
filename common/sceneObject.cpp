#include "sceneObject.h"

void sceneObject::render() {
    glBindVertexArray(model->VAO);
    glDrawArrays(GL_TRIANGLES, 0, model->elementCount);
    glBindVertexArray(0);
}

sceneObject::sceneObject(model3D * model, Material material, vec3 position) {
    this->model = model;
    this->material = material;
    this->position = position;
}

mat4 sceneObject::getModelTransform() {
    return {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        position.x, position.y, position.z, 1.0,
    };
}
