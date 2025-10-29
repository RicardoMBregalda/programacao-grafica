#include "Chair.h"
#include "Cube.h"

Chair::Chair(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}

Chair::Chair(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}

void Chair::init() {
    // ----- proporções realistas -----
    const float seatW = 0.8f;      // largura
    const float seatD = 0.65f;      // profundidade
    const float seatT = 0.06f;     // espessura do assento

    const float legH = 0.60f;      // altura da perna
    const float legT = 0.07f;      // espessura da perna

    const float backH = 1.0f;     // altura do encosto
    const float backT = 0.06f;     // espessura do encosto
    const float backTiltDeg = -10.0f;

    // ----- posições derivadas -----
    const float seatY = legH + seatT * 0.5f;       // centro do assento
    const float seatTopY = seatY + seatT * 0.5f;
    const float seatBackEdgeZ = -seatD * 0.5f;

    const float backCenterZ = seatBackEdgeZ - backT * 0.5f;
    const float backCenterY = seatTopY + backH * 0.5f;

    const float legOffsetX = seatW * 0.5f - legT * 0.5f;
    const float legOffsetZ = seatD * 0.5f - legT * 0.5f;
    const float legCenterY = legH * 0.5f;

    // ----- peças -----
    // Assento
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, seatY, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(seatW, seatT, seatD),
        0.0f
    ));

    // Encosto
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, backCenterY, backCenterZ),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(seatW, backH, backT),
        backTiltDeg
    ));

    // Pernas
    parts.push_back(std::make_unique<Cube>(glm::vec3( legOffsetX, legCenterY,  legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legOffsetX, legCenterY,  legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3( legOffsetX, legCenterY, -legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f));
    parts.push_back(std::make_unique<Cube>(glm::vec3(-legOffsetX, legCenterY, -legOffsetZ), glm::vec3(0.0f,1.0f,0.0f), glm::vec3(legT,legH,legT), 0.0f));
}

void Chair::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
