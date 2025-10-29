

#include "Bed.h"
#include "Cube.h"
#include "Cilindro.h"

Bed::Bed(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}

Bed::Bed(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}

void Bed::init() {
    // ===== Dimensões da cama (cama de casal) =====
    const float bedW = 1.6f;
    const float bedL = 2.0f;
    const float frameH = 0.35f;
    const float mattressH = 0.25f;
    const float headboardH = 0.80f;
    const float headboardT = 0.08f;

    const float frameY = frameH * 0.5f;
    const float mattressY = frameH + mattressH * 0.5f;
    const float headboardY = frameH + headboardH * 0.5f;
    const float headboardZ = bedL * 0.5f + headboardT * 0.5f;

    // ===== Base da cama =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, frameY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(bedW, frameH, bedL),
        0.0f
    ));

    // ===== Colchão =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, mattressY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(bedW - 0.1f, mattressH, bedL - 0.1f),
        0.0f
    ));

    // ===== Cabeceira =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, headboardY, headboardZ),
        glm::vec3(0.0f),
        glm::vec3(bedW - 0.1f, headboardH, headboardT),
        0.0f
    ));

    // ===== Travesseiros =====
    const float pillowW = 0.48f;
    const float pillowL = 0.33f;
    const float pillowH = 0.11f;
    const float pillowY = frameH + mattressH + pillowH * 0.5f;
    const float pillowZ = bedL * 0.30f;

    // Travesseiro esquerdo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-pillowW * 0.55f, pillowY, pillowZ),
        glm::vec3(0.0f),
        glm::vec3(pillowW, pillowH, pillowL),
        0.0f
    ));

    // Travesseiro direito
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(pillowW * 0.55f, pillowY, pillowZ),
        glm::vec3(0.0f),
        glm::vec3(pillowW, pillowH, pillowL),
        0.0f
    ));

    // ===== Pés da cama (4 pés cilíndricos) =====
    const float legR = 0.04f;
    const float legH = frameH;
    const float legX = bedW * 0.45f;
    const float legZ = bedL * 0.45f;
    const float legY = legH * 0.5f;

    // Pé frontal esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legX, legY, -legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 16
    ));

    // Pé frontal direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legX, legY, -legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 16
    ));

    // Pé traseiro esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legX, legY, legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 16
    ));

    // Pé traseiro direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legX, legY, legZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 16
    ));
}

void Bed::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
