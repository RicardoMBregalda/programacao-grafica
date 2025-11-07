#include "Rack.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Texture.h"
Rack::Rack(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood, Texture* metal)
    : Object(pos, rot, scl, ang), woodTexture(wood), metalTexture(metal) {
    init();
}
Rack::Rack(glm::vec3 pos, float ang, Texture* wood, Texture* metal)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), woodTexture(wood), metalTexture(metal) {
    init();
}
void Rack::init() {
    const float width = 1.80f;      
    const float depth = 0.40f;      
    const float height = 0.50f;     
    const float shelfH = 0.03f;     
    const float legH = 0.08f;       
    const float legR = 0.025f;      
    const float backH = 0.30f;      
    const float legY = legH * 0.5f;
    const float legX = width * 0.47f;
    const float legZ = depth * 0.45f;
    
    // Pé frontal esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legX, legY, legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 16,
        metalTexture  
    ));
    
    // Pé frontal direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legX, legY, legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 16,
        metalTexture  
    ));
    
    // Pé traseiro esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legX, legY, -legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 16,
        metalTexture  
    ));
    
    // Pé traseiro direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legX, legY, -legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 16,
        metalTexture  
    ));
    
    const float backY = legH + backH * 0.5f;
    const float backZ = -depth * 0.5f + 0.02f;
    const float backT = 0.02f;
    
    // Painel traseiro
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, backY, backZ),
        glm::vec3(0.0f),
        glm::vec3(width - 0.02f, backH, backT),
        0.0f,
        woodTexture  
    ));
    
    const float shelf1Y = legH + shelfH * 0.5f;
    
    // Prateleira inferior
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, shelf1Y, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width, shelfH, depth),
        0.0f,
        woodTexture  
    ));
    
    const float dividerH = backH - shelfH;
    const float dividerT = 0.02f;
    const float dividerY = legH + shelfH + dividerH * 0.5f;
    
    // Divisória esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-width * 0.25f, dividerY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(dividerT, dividerH, depth - 0.04f),
        0.0f,
        woodTexture  
    ));
    
    // Divisória direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(width * 0.25f, dividerY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(dividerT, dividerH, depth - 0.04f),
        0.0f,
        woodTexture  
    ));
    
    const float shelf2Y = legH + backH + shelfH * 0.5f;
    
    // Prateleira superior
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, shelf2Y, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width, shelfH, depth),
        0.0f,
        woodTexture  
    ));
    
    const float sideH = backH + shelfH;
    const float sideY = legH + sideH * 0.5f;
    const float sideT = 0.02f;
    
    // Lateral esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-width * 0.5f + sideT * 0.5f, sideY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(sideT, sideH, depth),
        0.0f,
        woodTexture  
    ));
    
    // Lateral direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(width * 0.5f - sideT * 0.5f, sideY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(sideT, sideH, depth),
        0.0f,
        woodTexture  
    ));
}
void Rack::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
