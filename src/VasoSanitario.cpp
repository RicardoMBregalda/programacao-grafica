#include "VasoSanitario.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Texture.h"

VasoSanitario::VasoSanitario(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, 
                             Texture* plastic)
    : Object(pos, rot, scl, ang), plasticTexture(plastic) {
    init();
}

VasoSanitario::VasoSanitario(glm::vec3 pos, float ang, Texture* plastic)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), plasticTexture(plastic) {
    init();
}

void VasoSanitario::init() {
    // ===== Dimensões do vaso sanitário =====
    const float baseW = 0.38f;      // Largura da base
    const float baseH = 0.10f;      // Altura da base
    const float baseD = 0.50f;      // Profundidade da base
    const float bowlW = 0.35f;      // Largura da bacia
    const float bowlH = 0.35f;      // Altura da bacia
    const float bowlD = 0.42f;      // Profundidade da bacia
    const float tankW = 0.30f;      // Largura da caixa d'água
    const float tankH = 0.35f;      // Altura da caixa d'água
    const float tankD = 0.15f;      // Profundidade da caixa d'água
    const float seatW = 0.36f;      // Largura do assento
    const float seatH = 0.03f;      // Espessura do assento
    const float seatD = 0.40f;      // Profundidade do assento

    // ===== BASE DO VASO =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, baseH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(baseW, baseH, baseD),
        0.0f,
        plasticTexture
    ));

    // ===== BACIA (corpo principal) =====
    const float bowlY = baseH + bowlH * 0.5f;
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, bowlY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(bowlW, bowlH, bowlD),
        0.0f,
        plasticTexture
    ));

    // ===== CAIXA D'ÁGUA (atrás) =====
    const float tankY = baseH + tankH * 0.5f;
    const float tankZ = -bowlD * 0.5f - tankD * 0.5f;
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, tankY, tankZ),
        glm::vec3(0.0f),
        glm::vec3(tankW, tankH, tankD),
        0.0f,
        plasticTexture
    ));

    // ===== ASSENTO (em cima da bacia) =====
    const float seatY = baseH + bowlH;
    
    // Anel do assento (simulado com cilindro achatado)
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, seatY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(seatW * 0.5f, seatH, seatD * 0.5f),
        0.0f,
        24,
        plasticTexture
    ));

    // Parte frontal do assento (cubo fino)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, seatY, seatD * 0.3f),
        glm::vec3(0.0f),
        glm::vec3(seatW * 0.8f, seatH, seatD * 0.25f),
        0.0f,
        plasticTexture
    ));

    // ===== TAMPA (levantada, atrás do assento) =====
    const float lidW = seatW;
    const float lidH = 0.42f;
    const float lidThick = 0.03f;
    const float lidY = seatY + lidH * 0.5f;
    const float lidZ = -seatD * 0.4f;
    
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, lidY, lidZ),
        glm::vec3(0.0f),
        glm::vec3(lidW, lidH, lidThick),
        0.0f,
        plasticTexture
    ));

    // ===== BOTÃO DE DESCARGA (topo da caixa d'água) =====
    const float buttonR = 0.04f;
    const float buttonH = 0.05f;
    const float buttonY = baseH + tankH + buttonH * 0.5f;
    
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, buttonY, tankZ),
        glm::vec3(0.0f),
        glm::vec3(buttonR, buttonH, buttonR),
        0.0f,
        16,
        plasticTexture
    ));
}

void VasoSanitario::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
