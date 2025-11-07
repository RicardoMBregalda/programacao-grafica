#include "Wardrobe.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "Texture.h"
Wardrobe::Wardrobe(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, 
                   Texture* wood, Texture* metal)
    : Object(pos, rot, scl, ang), woodTexture(wood), metalTexture(metal) {
    init();
}
Wardrobe::Wardrobe(glm::vec3 pos, float ang, Texture* wood, Texture* metal)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), 
      woodTexture(wood), metalTexture(metal) {
    init();
}
void Wardrobe::init() {
    const float width = 1.20f;
    const float height = 2.00f;
    const float depth = 0.60f;
    
    // Corpo principal do guarda-roupa
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, height * 0.5f, 0.0f),  
        glm::vec3(0.0f),
        glm::vec3(width, height, depth),
        0.0f,
        woodTexture  
    ));
    
    const float handleY = height * 0.5f;  
    const float handleZ = depth * 0.5f + 0.02f;  
    const float handleCylinderLength = 0.08f;  
    const float handleCylinderRadius = 0.035f; 
    const float handleSphereRadius = 0.085f;   
    const float handleOffsetX = width * 0.20f;  
    
    // Haste da maçaneta esquerda
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-handleOffsetX, handleY, handleZ),
        glm::vec3(1.0f, 0.0f, 0.0f),  
        glm::vec3(handleCylinderRadius, handleCylinderLength, handleCylinderRadius),
        90.0f,  
        16,
        metalTexture
    ));
    
    // Puxador esférico esquerdo
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(-handleOffsetX, handleY, handleZ + handleCylinderLength),
        glm::vec3(0.0f),
        glm::vec3(handleSphereRadius),
        0.0f, 12, 24,
        metalTexture
    ));
    
    // Haste da maçaneta direita
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(handleOffsetX, handleY, handleZ),
        glm::vec3(1.0f, 0.0f, 0.0f),  
        glm::vec3(handleCylinderRadius, handleCylinderLength, handleCylinderRadius),
        90.0f,  
        16,
        metalTexture
    ));
    
    // Puxador esférico direito
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(handleOffsetX, handleY, handleZ + handleCylinderLength),
        glm::vec3(0.0f),
        glm::vec3(handleSphereRadius),
        0.0f, 12, 24,
        metalTexture
    ));
}
void Wardrobe::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
