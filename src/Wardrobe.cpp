#include "Wardrobe.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "Texture.h"

Wardrobe::Wardrobe(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, 
                   Texture* wood, Texture* metal)
    : Object(pos, rot, scl, ang), woodTexture(wood), metalTexture(metal) {
    init();
}

Wardrobe::Wardrobe(glm::vec3 pos, float ang, Texture* wood, Texture* metal)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), 
      woodTexture(wood), metalTexture(metal) {
    init();
}

void Wardrobe::init() {
    // ===== Dimensões do guarda-roupa (bloco sólido simples) =====
    const float width = 1.20f;      // largura
    const float height = 2.00f;     // altura
    const float depth = 0.60f;      // profundidade

    // ===== Corpo principal - um único bloco sólido de madeira =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, height * 0.5f, 0.0f),  // Centrado na altura
        glm::vec3(0.0f),
        glm::vec3(width, height, depth),
        0.0f,
        woodTexture  // Textura de madeira
    ));

    // ===== Maçanetas (estilo porta: cilindro + esfera) =====
    // Parâmetros das maçanetas
    const float handleY = height * 0.5f;  // Altura média do armário
    const float handleZ = depth * 0.5f + 0.02f;  // Na frente do armário
    const float handleCylinderLength = 0.08f;  // Comprimento da haste
    const float handleCylinderRadius = 0.035f; // Raio da haste
    const float handleSphereRadius = 0.085f;   // Raio do puxador esférico
    
    // Posições das maçanetas (uma para cada "porta" virtual)
    const float handleOffsetX = width * 0.20f;  // Distância do centro

    // ===== Maçaneta esquerda =====
    // Cilindro (haste horizontal)
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-handleOffsetX, handleY, handleZ),
        glm::vec3(1.0f, 0.0f, 0.0f),  // Rotação para ficar horizontal
        glm::vec3(handleCylinderRadius, handleCylinderLength, handleCylinderRadius),
        90.0f,  // 90 graus no eixo X
        16,
        metalTexture
    ));
    
    // Esfera (puxador na ponta)
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(-handleOffsetX, handleY, handleZ + handleCylinderLength),
        glm::vec3(0.0f),
        glm::vec3(handleSphereRadius),
        0.0f, 12, 24,
        metalTexture
    ));

    // ===== Maçaneta direita =====
    // Cilindro (haste horizontal)
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(handleOffsetX, handleY, handleZ),
        glm::vec3(1.0f, 0.0f, 0.0f),  // Rotação para ficar horizontal
        glm::vec3(handleCylinderRadius, handleCylinderLength, handleCylinderRadius),
        90.0f,  // 90 graus no eixo X
        16,
        metalTexture
    ));
    
    // Esfera (puxador na ponta)
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(handleOffsetX, handleY, handleZ + handleCylinderLength),
        glm::vec3(0.0f),
        glm::vec3(handleSphereRadius),
        0.0f, 12, 24,
        metalTexture
    ));
}

void Wardrobe::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
