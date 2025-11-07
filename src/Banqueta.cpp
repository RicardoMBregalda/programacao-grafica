#include "Banqueta.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "Texture.h"
Banqueta::Banqueta(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* fabric, Texture* metal, Texture* plastic)
    : Object(pos, rot, scl, ang), fabricTexture(fabric), metalTexture(metal), plasticTexture(plastic) {
    init();
}
Banqueta::Banqueta(glm::vec3 pos, float ang, Texture* fabric, Texture* metal, Texture* plastic)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), fabricTexture(fabric), metalTexture(metal), plasticTexture(plastic) {
    init();
}
void Banqueta::init() {
    const float seatR = 0.30f;      
    const float seatH = 0.10f;      
    const float poleR = 0.05f;      
    const float poleH = 0.15f;      
    const float baseR = 0.20f;      
    const float baseH = 0.03f;      
    const float wheelR = 0.04f;     
    const float seatY = wheelR + baseH + poleH + seatH * 0.5f;
    
    // Assento estofado
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, seatY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(seatR, seatH, seatR),
        0.0f, 32,
        fabricTexture  
    ));
    
    const float poleY = wheelR + baseH + poleH * 0.5f;
    
    // Haste central de metal
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, poleY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(poleR, poleH, poleR),
        0.0f, 12,
        metalTexture  
    ));
    
    const float baseY = wheelR + baseH * 0.5f;
    
    // Base circular de metal
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, baseY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(baseR, baseH, baseR),
        0.0f, 32,
        metalTexture  
    ));
    
    const float wheelDist = baseR * 0.40f;
    const int numWheels = 5;
    
    // Rodinhas da base
    for (int i = 0; i < numWheels; i++) {
        float angle = (float)i * (360.0f / numWheels) * 3.14159f / 180.0f;
        float wx = wheelDist * cos(angle);
        float wz = wheelDist * sin(angle);
        parts.push_back(std::make_unique<Esfera>(
            glm::vec3(wx, wheelR, wz),
            glm::vec3(0.0f),
            glm::vec3(wheelR),
            0.0f, 12, 24,
            plasticTexture  
        ));
    }
}
void Banqueta::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
