#include "Lamp.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Prisma.h"
#include "Esfera.h"
#include "Texture.h"

Lamp::Lamp(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* metal, Texture* shade, Texture* bulb)
    : Object(pos, rot, scl, ang), metalTexture(metal), shadeTexture(shade), bulbTexture(bulb) {
    init();
}

Lamp::Lamp(glm::vec3 pos, float ang, Texture* metal, Texture* shade, Texture* bulb)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), metalTexture(metal), shadeTexture(shade), bulbTexture(bulb) {
    init();
}

void Lamp::init() {
    // ===== Dimensões da luminária =====
    const float baseR = 0.12f;      // raio da base
    const float baseH = 0.04f;      // altura da base
    const float shaftR = 0.02f;     // raio da haste
    const float shaftH = 0.50f;     // altura da haste
    const float shadeR = 0.15f;     // raio da cúpula
    const float shadeH = 0.25f;     // altura da cúpula
    const float bulbR = 0.05f;      // raio da lâmpada

    // ===== Base circular - USA metalTexture =====
    const float baseY = baseH * 0.5f;
    
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, baseY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(baseR, baseH, baseR),
        0.0f, 32,
        metalTexture  // Textura de metal na base
    ));

    // ===== Haste vertical - USA metalTexture =====
    const float shaftY = baseH + shaftH * 0.5f;
    
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(0.0f, shaftY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(shaftR, shaftH, shaftR),
        0.0f, 16,
        metalTexture  // Textura de metal na haste
    ));

    // ===== Conector esférico no topo - USA metalTexture =====
    const float connectorY = baseH + shaftH;
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, connectorY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.03f),
        0.0f, 12, 24,
        metalTexture  // Textura de metal no conector
    ));

    // ===== Lâmpada (esfera central) - USA bulbTexture =====
    const float bulbY = baseH + shaftH + 0.08f;
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, bulbY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(bulbR),
        0.0f, 16, 32,
        bulbTexture  // Textura da lâmpada (amarelo/branco)
    ));

    // ===== Cúpula (abajur) - múltiplos cilindros formando cone - USA shadeTexture =====
    const int layers = 5;
    const float topY = baseH + shaftH + 0.02f;
    
    for (int i = 0; i < layers; i++) {
        float t = (float)i / (float)(layers - 1);
        float layerH = shadeH / layers;
        float layerY = topY + t * shadeH + layerH * 0.5f;
        // Raio diminui conforme sobe (cone invertido)
        float layerR = shadeR * (1.0f - t * 0.6f);
        
        parts.push_back(std::make_unique<Cilindro>(
            glm::vec3(0.0f, layerY, 0.0f),
            glm::vec3(0.0f),
            glm::vec3(layerR, layerH, layerR),
            0.0f, 32,
            shadeTexture  // Textura da cúpula (tecido/plástico)
        ));
    }
}

void Lamp::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
