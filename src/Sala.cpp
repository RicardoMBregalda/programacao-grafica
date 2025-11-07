#include "Sala.h"
#include "Floor.h"
#include "Wall.h"
#include "Sofa.h"
#include "Table.h"
#include "Rack.h"
#include "TV.h"
#include "Chair.h"
#include "Texture.h"
#include <glm/gtc/matrix_transform.hpp>

Sala::Sala(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang,
           Texture* woodTex, Texture* metalTex, Texture* plasticTex,
           Texture* blackTex, Texture* fabricTex, Texture* stoneTex)
    : Object(pos, rot, scl, ang),
      woodTexture(woodTex),
      metalTexture(metalTex),
      plasticTexture(plasticTex),
      blackTexture(blackTex),
      fabricTexture(fabricTex),
      stoneTexture(stoneTex) {
    init();
}

Sala::Sala(glm::vec3 pos, float ang,
           Texture* woodTex, Texture* metalTex, Texture* plasticTex,
           Texture* blackTex, Texture* fabricTex, Texture* stoneTex)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang),
      woodTexture(woodTex),
      metalTexture(metalTex),
      plasticTexture(plasticTex),
      blackTexture(blackTex),
      fabricTexture(fabricTex),
      stoneTexture(stoneTex) {
    init();
}

void Sala::init() {
    createRoom();
    createLivingArea();
    createDiningArea();
}

void Sala::createRoom() {
    // Dimensões da sala: 10m (largura) x 8m (profundidade)
    
    // PISO (assoalho de madeira - bem grande)
    auto floor = std::make_unique<Floor>(
        glm::vec3(0.0f, 0.00f, 0.0f),  // Ligeiramente abaixo do nível 0
        0.0f,
        woodTexture
    );
    floor->scale = glm::vec3(10.0f, 0.1f, 8.0f);
    components.push_back(std::move(floor));

    // PAREDE DOS FUNDOS
    auto backWall = std::make_unique<Wall>(
        glm::vec3(0.0f, 1.5f, -4.0f),
        0.0f,
        stoneTexture
    );
    backWall->scale = glm::vec3(10.0f, 3.0f, 0.2f);
    components.push_back(std::move(backWall));

    // PAREDE LATERAL ESQUERDA
    auto leftWall = std::make_unique<Wall>(
        glm::vec3(-5.0f, 1.5f, 0.0f),
        90.0f,
        stoneTexture
    );
    leftWall->scale = glm::vec3(8.0f, 3.0f, 0.2f);
    components.push_back(std::move(leftWall));

    // PAREDE LATERAL DIREITA
    auto rightWall = std::make_unique<Wall>(
        glm::vec3(5.0f, 1.5f, 0.0f),
        90.0f,
        stoneTexture
    );
    rightWall->scale = glm::vec3(8.0f, 3.0f, 0.2f);
    components.push_back(std::move(rightWall));
}
void Sala::createLivingArea() {
    // Área de estar (lado esquerdo da sala)
    
    // SOFÁ (encostado na parede esquerda, virado para o centro)
    auto sofa = std::make_unique<Sofa>(
        glm::vec3(-1.8f, 0.0f, 0.0f),
        180.0f,  // Virado para a direita (para o centro)
        fabricTexture,
        woodTexture
    );
    sofa->scale = glm::vec3(1.0f);
    components.push_back(std::move(sofa));

    // MESA DE CENTRO (entre sofá e TV)
    auto coffeeTable = std::make_unique<Table>(
        glm::vec3(-1.8f, 0.0f, -1.8f),
        0.0f,
        woodTexture
    );
    coffeeTable->scale = glm::vec3(1.0f, 0.35f, 1.0f);  // Mesa pequena e baixa
    components.push_back(std::move(coffeeTable));

    // RACK DA TV (perto da parede dos fundos)
    auto rack = std::make_unique<Rack>(
        glm::vec3(-1.8f, 0.0f, -3.5f),
        0.0f,
        woodTexture,
        metalTexture
    );
    rack->scale = glm::vec3(1.25f, 1.25f, 1.25f);
    components.push_back(std::move(rack));

    // TV (sobre o rack)
    auto tv = std::make_unique<TV>(
        glm::vec3(-1.8f, 0.50f, -3.5f),
        0.0f,
        blackTexture,
        plasticTexture
    );
    tv->scale = glm::vec3(1.25f, 1.25f, 1.25f);
    components.push_back(std::move(tv));
}

void Sala::createDiningArea() {
    // Área de jantar (lado direito da sala)
    
    // MESA DE JANTAR - centralizada no lado direito
    auto diningTable = std::make_unique<Table>(
        glm::vec3(2.2f, 0.0f, -1.9f),
        0.0f,
        woodTexture
    );
    diningTable->scale = glm::vec3(1.0f, 1.0f, 2.5f);
    components.push_back(std::move(diningTable));

    // 6 CADEIRAS ao redor da mesa - com espaçamento adequado
    // Dimensões da mesa após escala: ~1.08m largura × ~0.56m profundidade
    
    // Cadeira 1 - Lado ESQUERDO (mais próximo do sofá) - FRONTAL
    auto chair1 = std::make_unique<Chair>(
        glm::vec3(1.6f, 0.0f, -2.3f),
        90.0f,  // Virada para direita (mesa)
        woodTexture,
        fabricTexture
    );
    chair1->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair1));

    // Cadeira 2 - Lado ESQUERDO - TRASEIRA
    auto chair2 = std::make_unique<Chair>(
        glm::vec3(1.6f, 0.0f, -1.5f),
        90.0f,
        woodTexture,
        fabricTexture
    );
    chair2->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair2));

    // Cadeira 3 - Lado DIREITO (mais próximo da parede) - FRONTAL
    auto chair3 = std::make_unique<Chair>(
        glm::vec3(2.8f, 0.0f, -2.3f),
        270.0f,  // Virada para esquerda (mesa)
        woodTexture,
        fabricTexture
    );
    chair3->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair3));

    // Cadeira 4 - Lado DIREITO - TRASEIRA
    auto chair4 = std::make_unique<Chair>(
        glm::vec3(2.8f, 0.0f, -1.4f),
        270.0f,
        woodTexture,
        fabricTexture
    );
    chair4->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair4));

    // Cadeira 5 - CABECEIRA FRONTAL (próximo à parede dos fundos)
    auto chair5 = std::make_unique<Chair>(
        glm::vec3(2.2f, 0.0f, -2.9f),
        0.0f,  // Virada para frente (em direção ao fundo da sala)
        woodTexture,
        fabricTexture
    );
    chair5->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair5));

    // Cadeira 6 - CABECEIRA TRASEIRA (mais próximo da entrada/câmera)
    auto chair6 = std::make_unique<Chair>(
        glm::vec3(2.2f, 0.0f, -0.9f),
        180.0f,  // Virada para trás (em direção à mesa)
        woodTexture,
        fabricTexture
    );
    chair6->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair6));
}

void Sala::draw(Shader& shader, glm::mat4 parentTransform) {
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
