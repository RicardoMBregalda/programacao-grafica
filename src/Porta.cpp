#include "Porta.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "Texture.h"

Porta::Porta(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood, Texture* metal)
    : Object(pos, rot, scl, ang), woodTexture(wood), metalTexture(metal) {
    init();
}

Porta::Porta(glm::vec3 pos, float ang, Texture* wood, Texture* metal)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), woodTexture(wood), metalTexture(metal) {
    init();
}

void Porta::init() {
    // Dimensões da porta
    const float doorW = 0.9f;   // largura da porta
    const float doorH = 2.0f;   // altura da porta
    const float doorT = 0.05f;  // espessura da porta
    const float frameT = 0.08f; // espessura do batente

    // BATENTE/FRAME (moldura ao redor)
    // Batente superior
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, doorH, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(doorW + frameT * 2, frameT, frameT),
        0.0f,
        woodTexture
    ));

    // Batente esquerdo
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-doorW * 0.5f - frameT * 0.5f, doorH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(frameT, doorH, frameT),
        0.0f,
        woodTexture
    ));

    // Batente direito
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(doorW * 0.5f + frameT * 0.5f, doorH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(frameT, doorH, frameT),
        0.0f,
        woodTexture
    ));

    // FOLHA DA PORTA FECHADA
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, doorH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(doorW, doorH, doorT),
        0.0f,
        woodTexture
    ));

    // MAÇANETAS (cilindro + esfera em ambos os lados, sempre à esquerda)
    const float handleHeight = doorH * 0.5f;  // Altura da maçaneta (meio da porta)
    const float handleXFront = -doorW * 0.35f;  // Posição X para lado FRONTAL (esquerda)
    const float handleXBack = doorW * 0.35f;    // Posição X para lado TRASEIRO (espelhado - direita)
    const float handleLength = 0.08f;         // Comprimento do cilindro (haste)
    const float handleRadius = 0.035f;        // Raio do cilindro
    const float knobRadius = 0.085f;          // Raio da esfera (puxador)

    // MAÇANETA FRONTAL (lado positivo Z) - ESQUERDA
    // Cilindro horizontal (haste da maçaneta)
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(handleXFront, handleHeight, doorT * 0.5f + handleLength * 0.5f),
        glm::vec3(1.0f, 0.0f, 0.0f),  // Eixo de rotação: X
        glm::vec3(handleRadius, handleLength, handleRadius),
        90.0f,           // Ângulo: 90° para ficar horizontal
        36,              // segments
        metalTexture
    ));

    // Esfera na ponta (puxador da maçaneta)
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(handleXFront, handleHeight, doorT * 0.5f + handleLength),
        glm::vec3(0.0f),
        glm::vec3(knobRadius),
        0.0f,
        18,              // stacks
        36,              // sectors
        metalTexture
    ));

    // MAÇANETA TRASEIRA (lado negativo Z) - DIREITA (espelhada para ficar à esquerda também)
    // Cilindro horizontal (haste da maçaneta)
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(handleXBack, handleHeight, -doorT * 0.5f - handleLength * 0.5f),
        glm::vec3(1.0f, 0.0f, 0.0f),  // Eixo de rotação: X
        glm::vec3(handleRadius, handleLength, handleRadius),
        90.0f,           // Ângulo: 90° para ficar horizontal
        36,              // segments
        metalTexture
    ));

    // Esfera na ponta (puxador da maçaneta)
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(handleXBack, handleHeight, -doorT * 0.5f - handleLength),
        glm::vec3(0.0f),
        glm::vec3(knobRadius),
        0.0f,
        18,              // stacks
        36,              // sectors
        metalTexture
    ));
}

void Porta::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    
    for (auto& p : parts)
        p->draw(shader, model);
}
