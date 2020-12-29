#include "sceneObject.h"
#include "../common/transformations.h"

void sceneObject::render() {
    glBindVertexArray(model->VAO);
    glDrawArrays(GL_TRIANGLES, 0, model->elementCount);
    glBindVertexArray(0);
}

sceneObject::sceneObject(model3D * model, Material material, vec4 position, vec4 scale) {
    this->model = model;
    this->material = material;
    this->position = position;
    this->scale = scale;
}

mat4 sceneObject::getModelTransform() {
    return scaleMatrix(scale) * rotationYMatrix(angleY) * offsetMatrix(position);
}

void sceneObject::rotateOY(GLfloat angle) {
    auto temp = vec4 { position.x, position.y, position.z, 1.0 };
    temp = rotationYMatrix(angle) * temp;
    angleY -= angle;
    position = { temp.x, temp.y, temp.z };
}
