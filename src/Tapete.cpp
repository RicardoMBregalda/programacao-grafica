#include "Tapete.h"
#include "Cilindro.h"
#include "Texture.h"
Tapete::Tapete(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* fabric)
    : Object(pos, rot, scl, ang), fabricTexture(fabric) {
    init();
}
Tapete::Tapete(glm::vec3 pos, float ang, Texture* fabric)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), fabricTexture(fabric) {
    init();
}
void Tapete::init() {
    const float rugRadius = 1.2f;    
    const float rugHeight = 0.02f;   
    const int segments = 36;         
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, rugHeight * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(rugRadius, rugHeight, rugRadius),
        0.0f,
        segments,
        fabricTexture  
    ));
}
void Tapete::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
