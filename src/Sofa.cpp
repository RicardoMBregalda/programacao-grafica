#include "Sofa.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Texture.h"

Sofa::Sofa(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* fabric, Texture* wood)
    : Object(pos, rot, scl, ang), fabricTexture(fabric), woodTexture(wood) {
    init();
}

Sofa::Sofa(glm::vec3 pos, float ang, Texture* fabric, Texture* wood)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), fabricTexture(fabric), woodTexture(wood) {
    init();
}

void Sofa::init() {
    // ===== Dimensões do sofá =====
    const float seatW = 1.8f;       // largura do assento (sofá de 3 lugares)
    const float seatD = 0.80f;      // profundidade do assento
    const float seatH = 0.45f;      // altura do assento
    const float seatY = 0.25f;      // altura do chão até o assento 
    
    const float backH = 0.70f;      // altura do encosto
    const float backT = 0.15f;      // espessura do encosto
    
    const float armW = 0.15f;       // largura dos braços
    const float armH = 0.75f;       // altura dos braços
  
    const float legR = 0.03f;       // raio dos pés
    const float legH = 0.10f;       // altura dos pés
   
    // ===== Assento principal =====
    const float seatCenterY = legH + seatH * 0.5f;
    
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, seatCenterY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(seatW, seatH, seatD),
        0.0f,
        fabricTexture  // Textura de tecido
    ));

    // ===== Encosto =====
    const float backY = legH + seatH + backH * 0.5f;
    const float backZ = -seatD * 0.5f + backT * 0.5f;
    
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, backY, backZ),
        glm::vec3(0.0f),
        glm::vec3(seatW, backH, backT),
        0.0f,
        fabricTexture  // Textura de tecido
    ));

    // ===== Braços laterais =====
    const float armX = seatW * 0.5f + armW * 0.5f;
    const float armY = legH + armH * 0.5f;
    
    // Braço esquerdo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-armX, armY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(armW, armH, seatD),
        0.0f,
        fabricTexture  // Textura de tecido
    ));

    // Braço direito
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(armX, armY, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(armW, armH, seatD),
        0.0f,
        fabricTexture  // Textura de tecido
    ));



    // ===== Pés (4 pés cilíndricos - MENORES) =====
    const float legOffsetX = seatW * 0.4f;
    const float legOffsetZ = seatD * 0.35f;
    const float legCenterY = legH * 0.5f;

    // Pé frontal esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legOffsetX, legCenterY, legOffsetZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  // Textura de madeira
    ));

    // Pé frontal direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legOffsetX, legCenterY, legOffsetZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  // Textura de madeira
    ));

    // Pé traseiro esquerdo
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(-legOffsetX, legCenterY, -legOffsetZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  // Textura de madeira
    ));

    // Pé traseiro direito
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(legOffsetX, legCenterY, -legOffsetZ),
        glm::vec3(0.0f),
        glm::vec3(legR, legH, legR),
        0.0f, 12,
        woodTexture  // Textura de madeira
    ));
}

void Sofa::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
