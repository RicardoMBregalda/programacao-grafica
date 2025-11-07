#include "Quarto.h"
#include "Floor.h"
#include "Wall.h"
#include "Bed.h"
#include "Nightstand.h"
#include "Lamp.h"
#include "Wardrobe.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>

Quarto::Quarto(glm::vec3 pos, float ang,
               Texture* woodTex, Texture* fabricTex, Texture* metalTex,
               Texture* bulbTex, Texture* wallTex)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang),
      woodTexture(woodTex),
      fabricTexture(fabricTex),
      metalTexture(metalTex),
      bulbTexture(bulbTex),
      wallTexture(wallTex) {
    init();
}

void Quarto::init() {
    createRoom();
    createFurniture();
}

void Quarto::createRoom() {
    // Dimensões do quarto: 4m (largura X) x 5m (profundidade Z)
    const float roomW = 4.0f;
    const float roomD = 5.0f;
    const float roomH = 3.0f;

    // PISO (mesma textura da sala)
    auto floor = std::make_unique<Floor>(
        glm::vec3(0.0f, 0.00f, 0.0f),
        0.0f,
        woodTexture
    );
    floor->scale = glm::vec3(roomW, 0.1f, roomD);
    components.push_back(std::move(floor));

    // PAREDE DOS FUNDOS (Z = -2.5)
    auto backWall = std::make_unique<Wall>(
        glm::vec3(0.0f, roomH * 0.5f, -roomD * 0.5f),
        0.0f,
        wallTexture
    );
    backWall->scale = glm::vec3(roomW, roomH, 0.2f);
    components.push_back(std::move(backWall));

    // PAREDE LATERAL DIREITA (X = +2.0)
    auto rightWall = std::make_unique<Wall>(
        glm::vec3(roomW * 0.5f, roomH * 0.5f, 0.0f),
        90.0f,
        wallTexture
    );
    rightWall->scale = glm::vec3(roomD, roomH, 0.2f);
    components.push_back(std::move(rightWall));
    
    // PAREDE FRONTAL (Z = +2.5)
    auto frontWall = std::make_unique<Wall>(
        glm::vec3(0.0f, roomH * 0.5f, roomD * 0.5f),
        0.0f,
        wallTexture
    );
    frontWall->scale = glm::vec3(roomW, roomH, 0.2f);
    components.push_back(std::move(frontWall));

    // A PAREDE ESQUERDA (X = -2.0) não é criada para conectar com a Sala.
}

void Quarto::createFurniture() {
    // CAMA (contra a parede dos fundos, de frente para a sala)
    // A cama (Bed.cpp) tem ~1.6W x 2.0L. A parede dos fundos está em Z=-2.5
    auto bed = std::make_unique<Bed>(
        glm::vec3(0.0f, 0.0f, -1.4f), // Posição (0, 0, -1.4) no quarto
        180.0f, // Rotação para ficar de frente para Z positivo
        woodTexture,
        fabricTexture
    );
    components.push_back(std::move(bed));

    // CRIADOS-MUDOS (Nightstand)
    // O Nightstand (Nightstand.cpp) tem 0.45W. A Cama tem 1.6W.
    float bedHalfW = 1.6f / 2.0f;
    float nsHalfW = 0.45f / 2.0f;
    float nsXPos = bedHalfW + nsHalfW + 0.1f; // Posição X para os criados
    float nsZPos = -2.2f; // Posição Z
    float nsH = 0.5f; // Altura do Nightstand (definida em Nightstand.cpp)

    // Nightstand 1 (Esquerda)
    auto ns1 = std::make_unique<Nightstand>(
        glm::vec3(-nsXPos, 0.0f, nsZPos),
        180.0f,
        woodTexture,
        metalTexture
    );
    components.push_back(std::move(ns1));

    // Nightstand 2 (Direita)
    auto ns2 = std::make_unique<Nightstand>(
        glm::vec3(nsXPos, 0.0f, nsZPos),
        180.0f,
        woodTexture,
        metalTexture
    );
    components.push_back(std::move(ns2));

    // LUMINÁRIAS (Lamp) em cima dos criados-mudos
    auto lamp1 = std::make_unique<Lamp>(
        glm::vec3(-nsXPos, nsH, nsZPos), // Posição Y = altura do criado-mudo
        0.0f,
        metalTexture,   // metal
        fabricTexture,  // shade (cúpula)
        bulbTexture     // bulb (lâmpada)
    );
    lamp1->scale = glm::vec3(0.6f); // Deixa a luminária um pouco menor
    components.push_back(std::move(lamp1));

    auto lamp2 = std::make_unique<Lamp>(
        glm::vec3(nsXPos, nsH, nsZPos),
        0.0f,
        metalTexture,
        fabricTexture,
        bulbTexture
    );
    lamp2->scale = glm::vec3(0.6f);
    components.push_back(std::move(lamp2));

    // GUARDA-ROUPA (Wardrobe)
    // Parede direita está em X = 2.0. Wardrobe (Wardrobe.cpp) tem 0.60D.
    // Posicionar em X = 2.0 - (0.60/2.0) = 1.7
    auto wardrobe = std::make_unique<Wardrobe>(
        glm::vec3(1.7f, 0.0f, 0.5f),
        270.0f, // Rotação para ficar de frente para o centro (X negativo)
        woodTexture,
        metalTexture
    );
    components.push_back(std::move(wardrobe));
}


void Quarto::draw(Shader& shader, glm::mat4 parentTransform) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    
    glm::mat4 currentTransform = parentTransform * modelMatrix;

    // Desenha todos os componentes
    for (auto& component : components) {
        component->draw(shader, currentTransform);
    }
}