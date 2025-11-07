#include "Prato.h"
#include "Cilindro.h"
#include "Texture.h"
Prato::Prato(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* plastic)
    : Object(pos, rot, scl, ang), plasticTexture(plastic) {
    init();
}
Prato::Prato(glm::vec3 pos, float ang, Texture* plastic)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), plasticTexture(plastic) {
    init();
}
void Prato::init() {
    const float plateRadius = 0.12f;  
    const float plateHeight = 0.015f; 
    const int segments = 32;          
    
    // Prato circular
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, plateHeight * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(plateRadius, plateHeight, plateRadius),
        0.0f,
        segments,
        plasticTexture  
    ));
}
void Prato::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
