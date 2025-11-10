#include "Banheiro.h"
#include "Floor.h"
#include "Wall.h"
#include "Pia.h"
#include "VasoSanitario.h"
#include "Tapete.h"
#include "Box.h"
#include "Chuveiro.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
Banheiro::Banheiro(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}
void Banheiro::init() {
    createRoom();
    createFixtures();
}
void Banheiro::createRoom() {
    auto& tex = TextureManager::getInstance();
    const float roomW = 3.0f;
    const float roomD = 3.0f;
    const float roomH = 2.5f;
    auto floor = std::make_unique<Floor>(
        glm::vec3(0.0f, 0.00f, 0.0f),
        0.0f,
        tex.bathroomFloor.get()
    );
    floor->scale = glm::vec3(roomW, 0.1f, roomD);
    components.push_back(std::move(floor));
    auto backWall = std::make_unique<Wall>(
        glm::vec3(0.0f, roomH * 0.5f, -roomD * 0.5f),
        0.0f,
        tex.tile_wall.get()
    );
    backWall->scale = glm::vec3(roomW, roomH, 0.2f);
    components.push_back(std::move(backWall));
    auto leftWall = std::make_unique<Wall>(
        glm::vec3(-roomW * 0.5f, roomH * 0.5f, 0.0f),
        90.0f,
        tex.tile_wall.get()
    );
    leftWall->scale = glm::vec3(roomD, roomH, 0.2f);
    components.push_back(std::move(leftWall));
    auto rightWall = std::make_unique<Wall>(
        glm::vec3(roomW * 0.5f, roomH * 0.5f, 0.0f),
        90.0f,
        tex.tile_wall.get()
    );
    rightWall->scale = glm::vec3(roomD, roomH, 0.2f);
    components.push_back(std::move(rightWall));
    auto frontWall = std::make_unique<Wall>(
        glm::vec3(0.0f, roomH * 0.5f, roomD * 0.5f),
        0.0f,
        tex.tile_wall.get()
    );
    frontWall->scale = glm::vec3(roomW, roomH, 0.2f);
    components.push_back(std::move(frontWall));
}
void Banheiro::createFixtures() {
    auto& tex = TextureManager::getInstance();
    auto pia = std::make_unique<Pia>(
        glm::vec3(1.1f, 0.0f, -0.8f),  
        270.0f,  
        tex.wood.get(),      // Armário em madeira
        tex.ceramics.get(),      // Pia em cerâmica
        tex.plastic.get()    // Torneira em plástico
    );
    pia->scale = glm::vec3(1.2f);
    components.push_back(std::move(pia));
    auto vaso = std::make_unique<VasoSanitario>(
        glm::vec3(-1.0f, 0.0f, -0.8f),  
        90.0f,  
        tex.ceramics.get()
    );
    vaso->scale = glm::vec3(1.2f);
    components.push_back(std::move(vaso));

    auto tapete = std::make_unique<Tapete>(
        glm::vec3(0.0f, 0.0f, -0.8f), 
        0.0f,
        tex.fabricLight.get()  
    );
    tapete->scale = glm::vec3(0.75f);
    components.push_back(std::move(tapete));

    auto box = std::make_unique<Box>(
        glm::vec3(-1.1f, 0.0f, 1.0f),
        0.0f,
        tex.glass.get(),
        tex.tile.get()
    );
    box->scale = glm::vec3(1.0f);
    components.push_back(std::move(box));

    auto chuveiro = std::make_unique<Chuveiro>(
        glm::vec3(-1.45f, 0.0f, 1.0f),
        180.0f,
        tex.metal.get()
    );
    chuveiro->scale = glm::vec3(1.0f);
    components.push_back(std::move(chuveiro));
}
void Banheiro::draw(Shader& shader, glm::mat4 parentTransform) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    glm::mat4 currentTransform = parentTransform * modelMatrix;
    for (auto& component : components) {
        component->draw(shader, currentTransform);
    }
}
