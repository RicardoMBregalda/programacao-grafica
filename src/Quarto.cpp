#include "Quarto.h"
#include "Floor.h"
#include "Wall.h"
#include "Bed.h"
#include "Nightstand.h"
#include "Lamp.h"
#include "Wardrobe.h"
#include "Rack.h"
#include "TV.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
Quarto::Quarto(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}
void Quarto::init() {
    createRoom();
    createFurniture();
}
void Quarto::createRoom() {
    auto& tex = TextureManager::getInstance();
    const float roomW = 4.0f;
    const float roomD = 5.0f;
    const float roomH = 3.0f;
    auto floor = std::make_unique<Floor>(
        glm::vec3(0.0f, 0.00f, 0.0f),
        0.0f,
        tex.floor.get()
    );
    floor->scale = glm::vec3(roomW, 0.1f, roomD);
    components.push_back(std::move(floor));
    auto backWall = std::make_unique<Wall>(
        glm::vec3(0.0f, roomH * 0.5f, -roomD * 0.5f),
        0.0f,
        tex.wall.get()
    );
    backWall->scale = glm::vec3(roomW, roomH, 0.2f);
    components.push_back(std::move(backWall));
    auto rightWall = std::make_unique<Wall>(
        glm::vec3(roomW * 0.5f, roomH * 0.5f, 0.0f),
        90.0f,
        tex.wall.get()
    );
    rightWall->scale = glm::vec3(roomD, roomH, 0.2f);
    components.push_back(std::move(rightWall));
    auto frontWall = std::make_unique<Wall>(
        glm::vec3(0.0f, roomH * 0.5f, roomD * 0.5f),
        0.0f,
        tex.wall.get()
    );
    frontWall->scale = glm::vec3(roomW, roomH, 0.2f);
    components.push_back(std::move(frontWall));
}
void Quarto::createFurniture() {
    auto& tex = TextureManager::getInstance();
    auto bed = std::make_unique<Bed>(
        glm::vec3(0.0f, 0.0f, -1.4f), 
        180.0f, 
        tex.bedframe.get(),
        tex.blanket.get(),        
        tex.fabricLight.get()    
    );
    components.push_back(std::move(bed));
    float bedHalfW = 1.6f / 2.0f;
    float nsHalfW = 0.45f / 2.0f;
    float nsXPos = bedHalfW + nsHalfW + 0.1f; 
    float nsZPos = -2.2f; 
    float nsH = 0.5f; 
    auto ns1 = std::make_unique<Nightstand>(
        glm::vec3(-nsXPos, 0.0f, nsZPos),
        180.0f,
        tex.wood3.get(),
        tex.metal.get()
    );
    components.push_back(std::move(ns1));
    auto ns2 = std::make_unique<Nightstand>(
        glm::vec3(nsXPos, 0.0f, nsZPos),
        180.0f,
        tex.wood3.get(),
        tex.metal.get()
    );
    components.push_back(std::move(ns2));
    auto lamp1 = std::make_unique<Lamp>(
        glm::vec3(-nsXPos, nsH, nsZPos), 
        0.0f,
        tex.metal.get(),    
        tex.fabric.get(),   
        tex.black.get()     
    );
    lamp1->scale = glm::vec3(0.6f); 
    components.push_back(std::move(lamp1));
    auto lamp2 = std::make_unique<Lamp>(
        glm::vec3(nsXPos, nsH, nsZPos),
        0.0f,
        tex.metal.get(),
        tex.fabric.get(),
        tex.black.get()
    );
    lamp2->scale = glm::vec3(0.6f);
    components.push_back(std::move(lamp2));
    auto wardrobe = std::make_unique<Wardrobe>(
        glm::vec3(1.6f, 0.0f, 0.5f),
        270.0f, 
        tex.wardrobe.get(),
        tex.metal.get()
    );
    wardrobe->scale = glm::vec3(1.2f);
    components.push_back(std::move(wardrobe));

    auto rack = std::make_unique<Rack>(
        glm::vec3(0.0f, 0.0f, 1.8f),
        180.0f,
        tex.wood3.get(),
        tex.metal.get()
    );
    rack->scale = glm::vec3(1.0f);
    components.push_back(std::move(rack));

    auto tv = std::make_unique<TV>(
        glm::vec3(0.0f, 0.50f, 1.8f),
        180.0f,
        tex.black.get(),
        tex.plastic.get()
    );
    tv->scale = glm::vec3(1.0f);
    components.push_back(std::move(tv));
}
void Quarto::draw(Shader& shader, glm::mat4 parentTransform) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    glm::mat4 currentTransform = parentTransform * modelMatrix;
    for (auto& component : components) {
        component->draw(shader, currentTransform);
    }
}