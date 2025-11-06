#include "Floor.h"
#include "Cube.h"
#include "Texture.h"

Floor::Floor(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* tex)
    : Object(pos, rot, scl, ang), floorTexture(tex) {
    init();
}

Floor::Floor(glm::vec3 pos, float ang, Texture* tex)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), floorTexture(tex) {
    init();
}

void Floor::init() {
    // Piso horizontal
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.1f, 1.0f),
        0.0f,
        floorTexture  // Textura do piso
    ));
}

void Floor::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
