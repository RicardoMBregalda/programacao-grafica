#include "Nightstand.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Texture.h"
Nightstand::Nightstand(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood, Texture* metal)
    : Object(pos, rot, scl, ang), woodTexture(wood), metalTexture(metal) {
    init();
}
Nightstand::Nightstand(glm::vec3 pos, float ang, Texture* wood, Texture* metal)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), woodTexture(wood), metalTexture(metal) {
    init();
}
void Nightstand::init() {
    const float width = 0.45f;
    const float depth = 0.40f;
    const float height = 0.50f;
    const float topH = 0.03f;
    const float legH = 0.08f;
    const float legR = 0.02f;
    const float legY = legH * 0.5f;
    const float bodyH = height - topH - legH;
    const float bodyY = legH + bodyH * 0.5f;
    const float topY = legH + bodyH + topH * 0.5f;
    
    // Corpo principal do criado-mudo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, bodyY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width - 0.01f, bodyH, depth - 0.01f),
        0.0f,
        woodTexture  
    ));
    
    // Tampo superior
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, topY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width + 0.02f, topH, depth + 0.02f),
        0.0f,
        woodTexture  
    ));
    
    const float drawerW = width - 0.04f;
    const float drawerH = (bodyH - 0.08f) / 3.0f;
    const float drawerD = 0.02f;
    const float drawerZ = depth * 0.5f + drawerD * 0.5f;
    const float gap = 0.015f;
    const float drawer1Y = legH + bodyH - drawerH * 0.5f - 0.02f;
    
    // Gaveta superior
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, drawer1Y, drawerZ),
        glm::vec3(0.0f),
        glm::vec3(drawerW, drawerH, drawerD),
        0.0f,
        woodTexture  
    ));
    
    // Puxador da gaveta superior
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, drawer1Y, drawerZ + drawerD * 0.5f + 0.015f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.008f, 0.06f, 0.008f),
        90.0f, 12,
        metalTexture  
    ));
    
    const float drawer2Y = drawer1Y - drawerH - gap;
    
    // Gaveta do meio
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, drawer2Y, drawerZ),
        glm::vec3(0.0f),
        glm::vec3(drawerW, drawerH, drawerD),
        0.0f,
        woodTexture  
    ));
    
    // Puxador da gaveta do meio
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, drawer2Y, drawerZ + drawerD * 0.5f + 0.015f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.008f, 0.06f, 0.008f),
        90.0f, 12,
        metalTexture  
    ));
    
    const float drawer3Y = drawer2Y - drawerH - gap;
    
    // Gaveta inferior
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, drawer3Y, drawerZ),
        glm::vec3(0.0f),
        glm::vec3(drawerW, drawerH, drawerD),
        0.0f,
        woodTexture  
    ));
    
    // Puxador da gaveta inferior
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, drawer3Y, drawerZ + drawerD * 0.5f + 0.015f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.008f, 0.06f, 0.008f),
        90.0f, 12,
        metalTexture  
    ));
    
    const float legX = (width - 0.01f) * 0.45f;
    const float legZ = (depth - 0.01f) * 0.45f;
    
    // Pé frontal esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legX, legY, legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  
    ));
    
    // Pé frontal direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legX, legY, legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  
    ));
    
    // Pé traseiro esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legX, legY, -legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  
    ));
    
    // Pé traseiro direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legX, legY, -legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  
    ));
}
void Nightstand::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
