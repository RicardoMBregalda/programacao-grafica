#include "TV.h"
#include "Cube.h"
#include "Cilindro.h"

TV::TV(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}

TV::TV(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}

void TV::init() {
    // ===== Dimensões da TV =====
    const float screenW = 1.6f;  // largura da tela
    const float screenH = 0.9f;  // altura da tela
    const float screenT = 0.08f; // espessura da tela
    
    const float frameW = 0.04f;  // largura da moldura
    const float totalW = screenW + frameW * 2.0f;
    const float totalH = screenH + frameW * 2.0f;
    
    const float standW = 0.50f;  // largura do suporte
    const float standH = 0.08f;  // altura do suporte
    const float standD = 0.25f;  // profundidade do suporte
    const float neckW = 0.10f;   // largura do pescoço
    const float neckH = 0.15f;   // altura do pescoço
    const float neckD = 0.10f;   // profundidade do pescoço

    // ===== Posições =====
    const float screenY = neckH + standH + screenH * 0.5f;
    const float frameY = screenY;
    const float neckY = standH + neckH * 0.5f;
    const float standY = standH * 0.5f;

    // ===== Tela (preta/azul escuro) =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, screenY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(screenW, screenH, screenT * 0.5f),
        0.0f
    ));

    // ===== Moldura (frame) =====
    // Moldura superior
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, screenY + screenH * 0.5f + frameW * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(totalW, frameW, screenT),
        0.0f
    ));

    // Moldura inferior
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, screenY - screenH * 0.5f - frameW * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(totalW, frameW, screenT),
        0.0f
    ));

    // Moldura esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-screenW * 0.5f - frameW * 0.5f, screenY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(frameW, screenH, screenT),
        0.0f
    ));

    // Moldura direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(screenW * 0.5f + frameW * 0.5f, screenY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(frameW, screenH, screenT),
        0.0f
    ));

    // ===== Parte traseira da TV =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, screenY, -screenT * 0.5f),
        glm::vec3(0.0f),
        glm::vec3(totalW - 0.02f, totalH - 0.02f, screenT * 0.3f),
        0.0f
    ));

    // ===== Pescoço/suporte vertical =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, neckY, -screenT * 0.3f),
        glm::vec3(0.0f),
        glm::vec3(neckW, neckH, neckD),
        0.0f
    ));

    // ===== Base/suporte horizontal =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, standY, -screenT * 0.3f),
        glm::vec3(0.0f),
        glm::vec3(standW, standH, standD),
        0.0f
    ));

    // ===== Pés arredondados (opcional, para melhor estética) =====
    const float footR = 0.02f;
    const float footH = 0.02f;
    const float footX = standW * 0.4f;
    const float footZ = standD * 0.3f;
    const float footY = footH * 0.5f;

    auto createFoot = [&](float x, float z) {
        parts.push_back(std::make_unique<Cilindro>(
            glm::vec3(x, footY, z - screenT * 0.3f),
            glm::vec3(0.0f),
            glm::vec3(footR, footH, footR),
            0.0f, 16
        ));
    };

    createFoot(footX, footZ);
    createFoot(-footX, footZ);
    createFoot(footX, -footZ);
    createFoot(-footX, -footZ);
}

void TV::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
