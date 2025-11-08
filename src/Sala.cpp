#include "Sala.h"
#include "Floor.h"
#include "Wall.h"
#include "Sofa.h"
#include "Table.h"
#include "Rack.h"
#include "TV.h"
#include "Chair.h"
#include "Tapete.h"
#include "Prato.h"
#include "Texture.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
Sala::Sala(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}
Sala::Sala(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}
void Sala::init() {
    createRoom();
    createLivingArea();
    createDiningArea();
}
void Sala::createRoom() {
    auto& tex = TextureManager::getInstance();
    auto floor = std::make_unique<Floor>(
        glm::vec3(0.0f, 0.00f, 0.0f), 
        0.0f,
        tex.floor.get()
    );
    floor->scale = glm::vec3(10.0f, 0.1f, 8.0f);
    components.push_back(std::move(floor));
    auto backWall = std::make_unique<Wall>(
        glm::vec3(0.0f, 1.5f, -4.0f),
        0.0f,
        tex.wall.get()
    );
    backWall->scale = glm::vec3(10.0f, 3.0f, 0.2f);
    components.push_back(std::move(backWall));
    auto leftWall = std::make_unique<Wall>(
        glm::vec3(-5.0f, 1.5f, 0.0f),
        90.0f,
        tex.wall.get()
    );
    leftWall->scale = glm::vec3(8.0f, 3.0f, 0.2f);
    components.push_back(std::move(leftWall));
    auto rightWall = std::make_unique<Wall>(
        glm::vec3(5.0f, 1.5f, 0.0f),
        90.0f,
        tex.wall.get()
    );
    rightWall->scale = glm::vec3(8.0f, 3.0f, 0.2f);
    components.push_back(std::move(rightWall));
    auto frontWall = std::make_unique<Wall>(
        glm::vec3(0.0f, 1.5f, 4.0f),
        0.0f,
        tex.wall.get()
    );
    frontWall->scale = glm::vec3(10.0f, 3.0f, 0.2f);
    components.push_back(std::move(frontWall));
}
void Sala::createLivingArea() {
    auto& tex = TextureManager::getInstance();
    auto sofa = std::make_unique<Sofa>(
        glm::vec3(-1.8f, 0.0f, 0.0f),
        180.0f,
        tex.sofa.get(),
        tex.wood.get()
    );
    sofa->scale = glm::vec3(1.0f);
    components.push_back(std::move(sofa));
    auto tapete = std::make_unique<Tapete>(
        glm::vec3(-1.8f, 0.0f, -1.8f), 
        0.0f,
        tex.fabricLight.get()  
    );
    tapete->scale = glm::vec3(3.0f);
    components.push_back(std::move(tapete));
    auto coffeeTable = std::make_unique<Table>(
        glm::vec3(-1.8f, 0.0f, -1.8f),
        0.0f,
        tex.wood.get(),   // Pernas em madeira
        tex.table.get()   // Tampo em table
    );
    coffeeTable->scale = glm::vec3(1.0f, 0.35f, 1.0f);
    components.push_back(std::move(coffeeTable));
    auto rack = std::make_unique<Rack>(
        glm::vec3(-1.8f, 0.0f, -3.5f),
        0.0f,
        tex.wood3.get(),
        tex.metal.get()
    );
    rack->scale = glm::vec3(1.25f, 1.25f, 1.25f);
    components.push_back(std::move(rack));
    auto tv = std::make_unique<TV>(
        glm::vec3(-1.8f, 0.50f, -3.5f),
        0.0f,
        tex.black.get(),
        tex.plastic.get()
    );
    tv->scale = glm::vec3(1.25f, 1.25f, 1.25f);
    components.push_back(std::move(tv));
}
void Sala::createDiningArea() {
    auto& tex = TextureManager::getInstance();
    auto diningTable = std::make_unique<Table>(
        glm::vec3(2.2f, 0.0f, -1.9f),
        0.0f,
        tex.wood.get(),   // Pernas em madeira
        tex.table.get()   // Tampo em table
    );
    diningTable->scale = glm::vec3(1.0f, 1.0f, 2.5f);
    components.push_back(std::move(diningTable));
    auto chair1 = std::make_unique<Chair>(
        glm::vec3(1.6f, 0.0f, -2.3f),
        90.0f,  
        tex.wood.get(),
        tex.fabric.get()
    );
    chair1->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair1));
    auto chair2 = std::make_unique<Chair>(
        glm::vec3(1.6f, 0.0f, -1.4f),
        90.0f,
        tex.wood.get(),
        tex.fabric.get()
    );
    chair2->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair2));
    auto chair3 = std::make_unique<Chair>(
        glm::vec3(2.8f, 0.0f, -2.3f),
        270.0f,  
        tex.wood.get(),
        tex.fabric.get()
    );
    chair3->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair3));
    auto chair4 = std::make_unique<Chair>(
        glm::vec3(2.8f, 0.0f, -1.4f),
        270.0f,
        tex.wood.get(),
        tex.fabric.get()
    );
    chair4->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair4));
    auto chair5 = std::make_unique<Chair>(
        glm::vec3(2.2f, 0.0f, -2.9f),
        0.0f, 
        tex.wood.get(),
        tex.fabric.get()
    );
    chair5->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair5));
    auto chair6 = std::make_unique<Chair>(
        glm::vec3(2.2f, 0.0f, -0.9f),
        180.0f, 
        tex.wood.get(),
        tex.fabric.get()
    );
    chair6->scale = glm::vec3(0.65f);
    components.push_back(std::move(chair6));
    const float tableHeight = 0.77f;
    const float plateY = tableHeight;
    auto plate1 = std::make_unique<Prato>(
        glm::vec3(1.85f, plateY, -2.3f),
        0.0f,
        tex.ceramics.get()
    );
    plate1->scale = glm::vec3(3.0f);
    components.push_back(std::move(plate1));
    auto plate2 = std::make_unique<Prato>(
        glm::vec3(1.85f, plateY, -1.4f),
        0.0f,
        tex.ceramics.get()
    );
    plate2->scale = glm::vec3(3.0f);
    components.push_back(std::move(plate2));
    auto plate3 = std::make_unique<Prato>(
        glm::vec3(2.55f, plateY, -2.3f),
        0.0f,
        tex.ceramics.get()
    );
    plate3->scale = glm::vec3(3.0f);
    components.push_back(std::move(plate3));
    auto plate4 = std::make_unique<Prato>(
        glm::vec3(2.55f, plateY, -1.4f),
        0.0f,
        tex.ceramics.get()
    );
    plate4->scale = glm::vec3(3.0f);
    components.push_back(std::move(plate4));
    auto plate5 = std::make_unique<Prato>(
        glm::vec3(2.2f, plateY, -2.6f),
        0.0f,
        tex.ceramics.get()
    );
    plate5->scale = glm::vec3(3.0f);
    components.push_back(std::move(plate5));
    auto plate6 = std::make_unique<Prato>(
        glm::vec3(2.2f, plateY, -1.2f),
        0.0f,
        tex.ceramics.get()
    );
    plate6->scale = glm::vec3(3.0f);
    components.push_back(std::move(plate6));
}
void Sala::draw(Shader& shader, glm::mat4 parentTransform) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    glm::mat4 currentTransform = parentTransform * modelMatrix;
    for (auto& component : components) {
        component->draw(shader, currentTransform);
    }
}
