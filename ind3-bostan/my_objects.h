#ifndef OPENGLABS_MY_OBJECTS_H
#define OPENGLABS_MY_OBJECTS_H

#include "../common/sceneObject.h"

static sceneObject * fox() {
    auto model = new model3D("../assets/models/fox/fox.obj", (float)(1.0f / 300.0f));
    auto texture = loadTex("../assets/models/fox/fox.png");
    Material material = { texture,
                          { 0.0f, 0.0f, 0.0f, 1.0f },
                          { 1.0f, 1.0f, 1.0f, 1.0f },
                          { 0.09f, 0.09f, 0.09f, 1.0f },
                          { 0.1f, 0.1f, 0.1f },
                          96.0f };
    return new sceneObject(model, material, { 0.5, -1.0, 0.5, 1.0 });
}

static sceneObject * tree() {
    auto model = new model3D("../assets/models/tree/tree.obj", (float)(1.0f / 15.0f));
    auto texture = loadTex("../assets/models/tree/tree.jpg");
    Material material = { texture,
                          { 0.0f, 0.0f, 0.0f, 1.0f },
                          { 1.0f, 1.0f, 1.0f, 1.0f },
                          { 1.0f, 1.0f, 1.0f, 1.0f },
                          { 0.1f, 0.1f, 0.1f },
                          10.0f };
    return new sceneObject(model, material, { 0.0, -1.0, 0.0, 1.0 });
}

static sceneObject * eye() {
    auto model = new model3D("../assets/models/eye/eye.obj", (float)(1.0f / 30.0f));
    auto texture = loadTex("../assets/models/eye/eye.png");
    Material material = { texture,
                          { 1.0f, 1.0f, 1.0f, 1.0f },
                          { 1.0f, 1.0f, 1.0f, 1.0f },
                          { 1.0f, 1.0f, 1.0f, 1.0f },
                          { 0.9f, 0.9f, 0.9f },
                          96.0f };
    return new sceneObject(model, material, { -1.0, 0.0, 0.0, 1.0 });
}

static sceneObject * floor() {
    auto model = new model3D("../assets/models/cube.obj");
    auto texture = loadTex("../assets/floor.jpg");
    Material material = { texture,
                          { 1.0f, 1.0f, 1.0f, 0.5f },
                          { 1.0f, 1.0f, 1.0f, 1.0f },
                          { 0.09f, 0.09f, 0.09f, 1.0f },
                          { 0.1f, 0.1f, 0.1f },
                          10.0f };
    return new sceneObject(model, material,
                           { 0.0, -1.0, 0.0, 1.0 },
                           { 1.0, 0.05, 1.0, 0.5f });
}

static sceneObject * boxes() {
    auto model = new model3D("../assets/models/boxes/boxes.obj", 1.0f / 5.0f);
    auto texture = loadTex("../assets/models/boxes/boxes.png");
    Material material = { texture,
                          { 1.0f, 1.0f, 1.0f, 0.5f },
                          { 1.0f, 1.0f, 1.0f, 1.0f },
                          { 0.09f, 0.09f, 0.09f, 1.0f },
                          { 0.1f, 0.1f, 0.1f },
                          10.0f };
    return new sceneObject(model, material, { -0.5, -1.0, -0.5, 1.0 });
}

#endif //OPENGLABS_MY_OBJECTS_H
