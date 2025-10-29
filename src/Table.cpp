#include "Table.h"
#include "Cube.h"

Table::Table(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}

Table::Table(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}

void Table::init() {
    // --- proporções em escala com a cadeira ---
    const float topW = 1.2f;     // largura (X)
    const float topD = 0.8f;     // profundidade (Z)
    const float topT = 0.08f;    // espessura do tampo (Y)

    const float legH = 0.68f;    // altura das pernas (~altura do tampo de mesa)
    const float legT = 0.07f;    // espessura das pernas

    // --- posições derivadas ---
    const float topY = legH + topT * 0.5f; // centro do tampo
    const float legCenterY = legH * 0.5f;  // centro das pernas
    const float legOffsetX = topW * 0.5f - legT * 0.5f;
    const float legOffsetZ = topD * 0.5f - legT * 0.5f;

    // --- peças ---
    // Tampo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, topY, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(topW, topT, topD),
        0.0f
    ));

    // Pernas (4)
    parts.push_back(std::make_unique<Cube>(glm::vec3( legOffsetX, legCenterY,  legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legOffsetX, legCenterY,  legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3( legOffsetX, legCenterY, -legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legOffsetX, legCenterY, -legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f));
}

void Table::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    for (auto &part : parts)
        part->draw(shader, model);
}
