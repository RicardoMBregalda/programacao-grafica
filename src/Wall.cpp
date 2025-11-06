#include "Wall.h"
#include "Cube.h"
#include "Texture.h"

Wall::Wall(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* tex)
    : Object(pos, rot, scl, ang), wallTexture(tex) {
    init();
}

Wall::Wall(glm::vec3 pos, float ang, Texture* tex)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), wallTexture(tex) {
    init();
}

void Wall::init() {
    // Parede vertical (cubo rotacionado 90 graus)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.1f, 1.0f),
        90.0f,
        wallTexture  // Textura da parede
    ));
}

void Wall::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
