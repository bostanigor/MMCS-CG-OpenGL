#include "sceneObject.h"

void sceneObject::render() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(model->VAO);
    glDrawArrays(GL_TRIANGLES, 0, model->elementCount);
    glBindVertexArray(0);
}

sceneObject::sceneObject(model3D * model, GLuint texture, Material material) {
    this->model = model;
    this->texture = texture;
    this->material = material;
    position = { 0.0f, 0.0f, 0.0f };
}
