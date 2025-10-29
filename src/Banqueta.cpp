#include "Banqueta.h"
#include "Cilindro.h"
#include "Esfera.h"

Banqueta::Banqueta(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}

Banqueta::Banqueta(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}

void Banqueta::init() {
    // ===== Dimensões da banqueta/puff =====
    const float seatR = 0.30f;      // raio do assento
    const float seatH = 0.10f;      // altura do assento (estofado)
    const float poleR = 0.05f;      // raio da haste central
    const float poleH = 0.15f;      // altura da haste
    const float baseR = 0.20f;      // raio da base
    const float baseH = 0.03f;      // altura da base
    const float wheelR = 0.04f;     // raio das rodinhas

    // ===== Assento principal (cilindro baixo e largo) =====
    const float seatY = wheelR + baseH + poleH + seatH * 0.5f;
    
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, seatY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(seatR, seatH, seatR),
        0.0f, 32
    ));

    // ===== Haste central =====
    const float poleY = wheelR + baseH + poleH * 0.5f;
    
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, poleY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(poleR, poleH, poleR),
        0.0f, 12
    ));

    // ===== Base circular =====
    const float baseY = wheelR + baseH * 0.5f;
    
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, baseY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(baseR, baseH, baseR),
        0.0f, 32
    ));

    // ===== Rodinhas (5 rodinhas ao redor da base) =====
    const float wheelDist = baseR * 0.40f;
    const int numWheels = 5;
    
    for (int i = 0; i < numWheels; i++) {
        float angle = (float)i * (360.0f / numWheels) * 3.14159f / 180.0f;
        float wx = wheelDist * cos(angle);
        float wz = wheelDist * sin(angle);
        
        parts.push_back(std::make_unique<Esfera>(
            glm::vec3(wx, wheelR, wz),
            glm::vec3(0.0f),
            glm::vec3(wheelR),
            0.0f, 12, 24
        ));
    }
}

void Banqueta::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
