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
    // ===== Dimensões do guarda-roupa =====
    const float width = 1.20f;      // largura
    const float height = 2.00f;     // altura
    const float depth = 0.60f;      // profundidade
    const float wallThick = 0.03f;  // espessura das paredes
    const float doorW = width * 0.48f; // largura de cada porta
    const float handleR = 0.02f;    // raio das maçanetas
    const float handleL = 0.12f;    // comprimento das maçanetas
    const float footR = 0.03f;      // raio dos pés

    // ===== Base =====
    const float baseY = 0.05f;
    
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, baseY * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width, baseY, depth),
        0.0f,
        woodTexture  // Textura de madeira
    ));

    // ===== Corpo principal (caixa) =====
    const float bodyY = baseY + height * 0.5f;
    
    // Parede traseira
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, bodyY, -depth * 0.5f + wallThick * 0.5f),
        glm::vec3(0.0f),
        glm::vec3(width, height, wallThick),
        0.0f,
        woodTexture  // Textura de madeira
    ));
    
    // Parede esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-width * 0.5f + wallThick * 0.5f, bodyY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, height, depth),
        0.0f,
        woodTexture  // Textura de madeira
    ));
    
    // Parede direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(width * 0.5f - wallThick * 0.5f, bodyY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, height, depth),
        0.0f,
        woodTexture  // Textura de madeira
    ));
    
    // Teto
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, baseY + height - wallThick * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width, wallThick, depth),
        0.0f,
        woodTexture  // Textura de madeira
    ));
    
    // Piso interno
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, baseY + wallThick * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width, wallThick, depth),
        0.0f,
        woodTexture  // Textura de madeira
    ));

   



    // ===== Portas (2 portas) =====
    const float doorH = height - wallThick * 2.0f;
    const float doorThick = 0.04f;
    const float doorZ = depth * 0.5f - doorThick * 0.5f;
    
    // Porta esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-width * 0.25f, bodyY, doorZ),
        glm::vec3(0.0f),
        glm::vec3(doorW, doorH, doorThick),
        0.0f,
        woodTexture  // Textura de madeira
    ));
    
    // Porta direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(width * 0.25f, bodyY, doorZ),
        glm::vec3(0.0f),
        glm::vec3(doorW, doorH, doorThick),
        0.0f,
        woodTexture  // Textura de madeira
    ));

    // ===== Maçanetas cilíndricas (horizontais) =====
    const float handleY = bodyY;
    const float handleZ = doorZ + doorThick * 0.5f + handleR;
    
    // Maçaneta esquerda
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-width * 0.15f, handleY, handleZ),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(handleR, handleL, handleR),
        90.0f, 16,
        metalTexture  // Textura de metal
    ));
    
    // Maçaneta direita
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(width * 0.15f, handleY, handleZ),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(handleR, handleL, handleR),
        90.0f, 16,
        metalTexture  // Textura de metal
    ));

    // ===== Pés esféricos (4 cantos) =====
    const float footY = footR * 0.5f;
    const float footX = width * 0.5f - footR;
    const float footZ = depth * 0.5f - footR;
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(footX, footY, footZ),
        glm::vec3(0.0f),
        glm::vec3(footR),
        0.0f, 12, 24,
        woodTexture  // Textura de madeira
    ));
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(-footX, footY, footZ),
        glm::vec3(0.0f),
        glm::vec3(footR),
        0.0f, 12, 24,
        woodTexture  // Textura de madeira
    ));
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(footX, footY, -footZ),
        glm::vec3(0.0f),
        glm::vec3(footR),
        0.0f, 12, 24,
        woodTexture  // Textura de madeira
    ));
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(-footX, footY, -footZ),
        glm::vec3(0.0f),
        glm::vec3(footR),
        0.0f, 12, 24,
        woodTexture  // Textura de madeira
    ));
}

void Wardrobe::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
