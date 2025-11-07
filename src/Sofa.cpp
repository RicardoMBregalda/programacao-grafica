#include "Sofa.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Texture.h"
Sofa::Sofa(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* fabric, Texture* wood)
    : Object(pos, rot, scl, ang), fabricTexture(fabric), woodTexture(wood) {
    init();
}
Sofa::Sofa(glm::vec3 pos, float ang, Texture* fabric, Texture* wood)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), fabricTexture(fabric), woodTexture(wood) {
    init();
}
void Sofa::init() {
    const float seatW = 1.8f;       
    const float seatD = 0.80f;      
    const float seatH = 0.45f;      
    const float seatY = 0.25f;      
    const float backH = 0.70f;      
    const float backT = 0.15f;      
    const float armW = 0.15f;       
    const float armH = 0.75f;       
    const float legR = 0.03f;       
    const float legH = 0.10f;       
    const float seatCenterY = legH + seatH * 0.5f;
    
    // Assento estofado
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, seatCenterY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(seatW, seatH, seatD),
        0.0f,
        fabricTexture  
    ));
    
    const float backY = legH + seatH + backH * 0.5f;
    const float backZ = -seatD * 0.5f + backT * 0.5f;
    
    // Encosto do sofá
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, backY, backZ),
        glm::vec3(0.0f),
        glm::vec3(seatW, backH, backT),
        0.0f,
        fabricTexture  
    ));
    
    const float armX = seatW * 0.5f + armW * 0.5f;
    const float armY = legH + armH * 0.5f;
    
    // Braço esquerdo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-armX, armY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(armW, armH, seatD),
        0.0f,
        fabricTexture  
    ));
    
    // Braço direito
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(armX, armY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(armW, armH, seatD),
        0.0f,
        fabricTexture  
    ));
    
    const float legOffsetX = seatW * 0.4f;
    const float legOffsetZ = seatD * 0.35f;
    const float legCenterY = legH * 0.5f;
    
    // Pé frontal esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legOffsetX, legCenterY, legOffsetZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  
    ));
    
    // Pé frontal direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legOffsetX, legCenterY, legOffsetZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  
    ));
    
    // Pé traseiro esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legOffsetX, legCenterY, -legOffsetZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  
    ));
    
    // Pé traseiro direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legOffsetX, legCenterY, -legOffsetZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  
    ));
}
void Sofa::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
