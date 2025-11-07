#include "Pia.h"
#include "Cube.h"
#include "Texture.h"

Pia::Pia(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, 
         Texture* wood, Texture* metal)
    : Object(pos, rot, scl, ang), woodTexture(wood), metalTexture(metal) {
    init();
}

Pia::Pia(glm::vec3 pos, float ang, Texture* wood, Texture* metal)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), 
      woodTexture(wood), metalTexture(metal) {
    init();
}

void Pia::init() {
    // ===== Dimensões da pia =====
    const float cabinetW = 0.80f;    // Largura do móvel
    const float cabinetH = 0.85f;    // Altura do móvel
    const float cabinetD = 0.55f;    // Profundidade do móvel
    const float doorW = cabinetW * 0.48f; // Largura de cada porta
    const float doorH = cabinetH * 0.75f; // Altura das portas
    const float doorThick = 0.03f;   // Espessura das portas
    const float sinkW = 0.50f;       // Largura da cuba
    const float sinkD = 0.40f;       // Profundidade da cuba
    const float sinkDepth = 0.15f;   // Profundidade interna da cuba
    const float wallThick = 0.03f;   // Espessura das paredes da cuba
    
    // ===== MÓVEL DE BAIXO (corpo maciço) =====
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, cabinetH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(cabinetW, cabinetH, cabinetD),
        0.0f,
        woodTexture
    ));
    
    // ===== PORTAS DO MÓVEL (2 portas na frente) =====
    const float doorY = cabinetH * 0.5f;
    const float doorZ = cabinetD * 0.5f + doorThick * 0.5f;
    
    // Porta esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-cabinetW * 0.25f, doorY, doorZ),
        glm::vec3(0.0f),
        glm::vec3(doorW, doorH, doorThick),
        0.0f,
        woodTexture
    ));
    
    // Porta direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(cabinetW * 0.25f, doorY, doorZ),
        glm::vec3(0.0f),
        glm::vec3(doorW, doorH, doorThick),
        0.0f,
        woodTexture
    ));
    
    // ===== PUXADORES DAS PORTAS (pequenos cubos) =====
    const float handleW = 0.015f;
    const float handleH = 0.08f;
    const float handleZ = doorZ + doorThick * 0.5f + handleW * 0.5f;
    
    // Puxador esquerdo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-cabinetW * 0.15f, doorY, handleZ),
        glm::vec3(0.0f),
        glm::vec3(handleW, handleH, handleW),
        0.0f,
        metalTexture
    ));
    
    // Puxador direito
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(cabinetW * 0.15f, doorY, handleZ),
        glm::vec3(0.0f),
        glm::vec3(handleW, handleH, handleW),
        0.0f,
        metalTexture
    ));
    
    // ===== CUBA DA PIA (quadrada, externa) =====
    const float sinkBaseY = cabinetH;
    
    // Fundo da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, sinkBaseY + wallThick * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(sinkW, wallThick, sinkD),
        0.0f,
        metalTexture
    ));
    
    // Parede frontal da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, sinkBaseY + sinkDepth * 0.5f, sinkD * 0.5f - wallThick * 0.5f),
        glm::vec3(0.0f),
        glm::vec3(sinkW, sinkDepth, wallThick),
        0.0f,
        metalTexture
    ));
    
    // Parede traseira da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, sinkBaseY + sinkDepth * 0.5f, -sinkD * 0.5f + wallThick * 0.5f),
        glm::vec3(0.0f),
        glm::vec3(sinkW, sinkDepth, wallThick),
        0.0f,
        metalTexture
    ));
    
    // Parede esquerda da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-sinkW * 0.5f + wallThick * 0.5f, sinkBaseY + sinkDepth * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, sinkDepth, sinkD),
        0.0f,
        metalTexture
    ));
    
    // Parede direita da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(sinkW * 0.5f - wallThick * 0.5f, sinkBaseY + sinkDepth * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, sinkDepth, sinkD),
        0.0f,
        metalTexture
    ));
    
    // ===== TORNEIRA =====
    const float faucetY = cabinetH + sinkDepth;
    const float faucetZ = -sinkD * 0.47f; // Um pouco atrás do centro
    
    // Corpo principal da torneira (cubo maior vertical)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, faucetY + 0.15f, faucetZ),
        glm::vec3(0.0f),
        glm::vec3(0.04f, 0.30f, 0.04f),
        0.0f,
        metalTexture
    ));
    
    // Bico da torneira (cubo horizontal)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, faucetY + 0.20f, faucetZ + 0.08f),
        glm::vec3(0.0f),
        glm::vec3(0.03f, 0.03f, 0.12f),
        0.0f,
        metalTexture
    ));
    
    // Abridor esquerdo (cubo pequeno)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.06f, faucetY + 0.02f, faucetZ),
        glm::vec3(0.0f),
        glm::vec3(0.025f, 0.05f, 0.025f),
        0.0f,
        metalTexture
    ));
    
    // Abridor direito (cubo pequeno)
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.06f, faucetY + 0.02f, faucetZ),
        glm::vec3(0.0f),
        glm::vec3(0.025f, 0.05f, 0.025f),
        0.0f,
        metalTexture
    ));
}

void Pia::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);

    for (auto &p : parts)
        p->draw(shader, model);
}
