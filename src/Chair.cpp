#include "Chair.h"
#include "Cube.h"
#include "Texture.h"
Chair::Chair(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood, Texture* fabric)
    : Object(pos, rot, scl, ang), woodTexture(wood), fabricTexture(fabric) {
    init();
}
Chair::Chair(glm::vec3 pos, float ang, Texture* wood, Texture* fabric)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), woodTexture(wood), fabricTexture(fabric) {
    init();
}
void Chair::init() {
    const float seatW = 0.8f;      
    const float seatD = 0.65f;      
    const float seatT = 0.06f;     
    const float legH = 0.60f;      
    const float legT = 0.07f;      
    const float backH = 1.0f;     
    const float backT = 0.06f;     
    const float backTiltDeg = -10.0f;
    const float seatY = legH + seatT * 0.5f;       
    const float seatTopY = seatY + seatT * 0.5f;
    const float seatBackEdgeZ = -seatD * 0.5f;
    const float backCenterZ = seatBackEdgeZ - backT * 0.5f;
    const float backCenterY = seatTopY + backH * 0.5f;
    const float legOffsetX = seatW * 0.5f - legT * 0.5f;
    const float legOffsetZ = seatD * 0.5f - legT * 0.5f;
    const float legCenterY = legH * 0.5f;
    
    // Assento estofado
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, seatY, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(seatW, seatT, seatD),
        0.0f,
        fabricTexture
    ));
    
    // Encosto estofado
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, backCenterY, backCenterZ),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(seatW, backH, backT),
        backTiltDeg,
        fabricTexture
    ));
    
    // Pé frontal direito
    parts.push_back(std::make_unique<Cube>(glm::vec3( legOffsetX, legCenterY,  legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f, woodTexture));
    
    // Pé frontal esquerdo
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legOffsetX, legCenterY,  legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f, woodTexture));
    
    // Pé traseiro direito
    parts.push_back(std::make_unique<Cube>(glm::vec3( legOffsetX, legCenterY, -legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f, woodTexture));
    
    // Pé traseiro esquerdo
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legOffsetX, legCenterY, -legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f, woodTexture));
}
void Chair::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
