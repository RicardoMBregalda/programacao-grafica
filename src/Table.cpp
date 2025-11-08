#include "Table.h"
#include "Cube.h"
#include "Texture.h"
Table::Table(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood, Texture* tableTop)
    : Object(pos, rot, scl, ang), woodTexture(wood), tableTopTexture(tableTop) {
    init();
}
Table::Table(glm::vec3 pos, float ang, Texture* wood, Texture* tableTop)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), woodTexture(wood), tableTopTexture(tableTop) {
    init();
}
void Table::init() {
    const float topW = 1.2f;     
    const float topD = 0.8f;     
    const float topT = 0.08f;    
    const float legH = 0.68f;    
    const float legT = 0.07f;    
    const float topY = legH + topT * 0.5f; 
    const float legCenterY = legH * 0.5f;  
    const float legOffsetX = topW * 0.5f - legT * 0.5f;
    const float legOffsetZ = topD * 0.5f - legT * 0.5f;
    
    // Tampo da mesa
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, topY, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(topW, topT, topD),
        0.0f,
        tableTopTexture  
    ));
    
    // Perna frontal direita
    parts.push_back(std::make_unique<Cube>(glm::vec3( legOffsetX, legCenterY,  legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f, woodTexture));
    
    // Perna frontal esquerda
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legOffsetX, legCenterY,  legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f, woodTexture));
    
    // Perna traseira direita
    parts.push_back(std::make_unique<Cube>(glm::vec3( legOffsetX, legCenterY, -legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f, woodTexture));
    
    // Perna traseira esquerda
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legOffsetX, legCenterY, -legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f, woodTexture));
}
void Table::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &part : parts)
        part->draw(shader, model);
}
