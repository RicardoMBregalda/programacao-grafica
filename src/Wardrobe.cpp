#include "Wardrobe.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Esfera.h"

Wardrobe::Wardrobe(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}

Wardrobe::Wardrobe(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
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
        0.0f
    ));

    // ===== Corpo principal (caixa) =====
    const float bodyY = baseY + height * 0.5f;
    
    // Parede traseira
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, bodyY, -depth * 0.5f + wallThick * 0.5f),
        glm::vec3(0.0f),
        glm::vec3(width, height, wallThick),
        0.0f
    ));
    
    // Parede esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-width * 0.5f + wallThick * 0.5f, bodyY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, height, depth),
        0.0f
    ));
    
    // Parede direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(width * 0.5f - wallThick * 0.5f, bodyY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, height, depth),
        0.0f
    ));
    
    // Teto
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, baseY + height - wallThick * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width, wallThick, depth),
        0.0f
    ));
    
    // Piso interno
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, baseY + wallThick * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(width, wallThick, depth),
        0.0f
    ));

    // ===== Divisória central vertical =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, bodyY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, height, depth - wallThick * 2.0f),
        0.0f
    ));

    // ===== Prateleiras (3 prateleiras em cada lado) =====
    const float shelfThick = 0.02f;
    const float shelfW = (width - wallThick * 3.0f) * 0.5f;
    const float shelfD = depth - wallThick * 2.0f;
    
    for (int side = 0; side < 2; side++) {
        float sideX = (side == 0) ? -width * 0.25f : width * 0.25f;
        
        for (int i = 0; i < 3; i++) {
            float shelfY = baseY + wallThick + (i + 1) * (height - wallThick * 2.0f) * 0.25f;
            
            parts.push_back(std::make_unique<Cube>(
                glm::vec3(sideX, shelfY, 0.0f),
                glm::vec3(0.0f),
                glm::vec3(shelfW, shelfThick, shelfD),
                0.0f
            ));
        }
    }

    // ===== Portas (2 portas) =====
    const float doorH = height - wallThick * 2.0f;
    const float doorThick = 0.04f;
    const float doorZ = depth * 0.5f - doorThick * 0.5f;
    
    // Porta esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-width * 0.25f, bodyY, doorZ),
        glm::vec3(0.0f),
        glm::vec3(doorW, doorH, doorThick),
        0.0f
    ));
    
    // Porta direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(width * 0.25f, bodyY, doorZ),
        glm::vec3(0.0f),
        glm::vec3(doorW, doorH, doorThick),
        0.0f
    ));

    // ===== Maçanetas cilíndricas (horizontais) =====
    const float handleY = bodyY;
    const float handleZ = doorZ + doorThick * 0.5f + handleR;
    
    // Maçaneta esquerda
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-width * 0.15f, handleY, handleZ),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(handleR, handleL, handleR),
        90.0f, 16
    ));
    
    // Maçaneta direita
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(width * 0.15f, handleY, handleZ),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(handleR, handleL, handleR),
        90.0f, 16
    ));

    // ===== Pés esféricos (4 cantos) =====
    const float footY = footR * 0.5f;
    const float footX = width * 0.5f - footR;
    const float footZ = depth * 0.5f - footR;
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(footX, footY, footZ),
        glm::vec3(0.0f),
        glm::vec3(footR),
        0.0f, 12, 24
    ));
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(-footX, footY, footZ),
        glm::vec3(0.0f),
        glm::vec3(footR),
        0.0f, 12, 24
    ));
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(footX, footY, -footZ),
        glm::vec3(0.0f),
        glm::vec3(footR),
        0.0f, 12, 24
    ));
    
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(-footX, footY, -footZ),
        glm::vec3(0.0f),
        glm::vec3(footR),
        0.0f, 12, 24
    ));
}

void Wardrobe::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
