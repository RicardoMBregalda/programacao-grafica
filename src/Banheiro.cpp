#include "Banheiro.h"
#include "Floor.h"
#include "Wall.h"
#include "Pia.h"
#include "VasoSanitario.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>

Banheiro::Banheiro(glm::vec3 pos, float ang,
                   Texture* woodTex, Texture* metalTex, Texture* plasticTex,
                   Texture* wallTex, Texture* floorTex)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang),
      woodTexture(woodTex),
      metalTexture(metalTex),
      plasticTexture(plasticTex),
      wallTexture(wallTex),
      floorTexture(floorTex) {
    init();
}

void Banheiro::init() {
    createRoom();
    createFixtures();
}

void Banheiro::createRoom() {
    // Dimensões do banheiro: 3m (largura X) x 3m (profundidade Z)
    const float roomW = 3.0f;
    const float roomD = 3.0f;
    const float roomH = 2.5f;

    // PISO
    auto floor = std::make_unique<Floor>(
        glm::vec3(0.0f, 0.00f, 0.0f),
        0.0f,
        floorTexture
    );
    floor->scale = glm::vec3(roomW, 0.1f, roomD);
    components.push_back(std::move(floor));

    // PAREDE DOS FUNDOS (Z = -1.5)
    auto backWall = std::make_unique<Wall>(
        glm::vec3(0.0f, roomH * 0.5f, -roomD * 0.5f),
        0.0f,
        wallTexture
    );
    backWall->scale = glm::vec3(roomW, roomH, 0.2f);
    components.push_back(std::move(backWall));

    // PAREDE LATERAL ESQUERDA (X = -1.5)
    auto leftWall = std::make_unique<Wall>(
        glm::vec3(-roomW * 0.5f, roomH * 0.5f, 0.0f),
        90.0f,
        wallTexture
    );
    leftWall->scale = glm::vec3(roomD, roomH, 0.2f);
    components.push_back(std::move(leftWall));

    // PAREDE LATERAL DIREITA (X = +1.5)
    auto rightWall = std::make_unique<Wall>(
        glm::vec3(roomW * 0.5f, roomH * 0.5f, 0.0f),
        90.0f,
        wallTexture
    );
    rightWall->scale = glm::vec3(roomD, roomH, 0.2f);
    components.push_back(std::move(rightWall));

    // PAREDE FRONTAL (Z = +1.5) - onde ficaria a porta
    auto frontWall = std::make_unique<Wall>(
        glm::vec3(0.0f, roomH * 0.5f, roomD * 0.5f),
        0.0f,
        wallTexture
    );
    frontWall->scale = glm::vec3(roomW, roomH, 0.2f);
    components.push_back(std::move(frontWall));
}

void Banheiro::createFixtures() {
    // PIA - encostada na parede esquerda
    // Parede esquerda está em X = -1.5
    // Pia tem profundidade de ~0.55m, então posicionar em X = -1.5 + 0.55/2 + margem
    auto pia = std::make_unique<Pia>(
        glm::vec3(1.1f, 0.0f, -0.8f),  // Parede esquerda, um pouco para trás
        270.0f,  // Rotação de 270° para ficar de frente para o centro
        woodTexture,
        metalTexture
    );
    pia->scale = glm::vec3(1.2f);
    components.push_back(std::move(pia));

    // VASO SANITÁRIO - em frente à pia (do outro lado do banheiro)
    // Pia está em X = 1.1, vaso no lado oposto
    auto vaso = std::make_unique<VasoSanitario>(
        glm::vec3(-1.0f, 0.0f, -0.8f),  // Do lado oposto da pia
        90.0f,  // Rotação de 90° para ficar de frente para a pia
        plasticTexture
    );
    vaso->scale = glm::vec3(1.2f);
    components.push_back(std::move(vaso));
}

void Banheiro::draw(Shader& shader, glm::mat4 parentTransform) {
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
