#include "Porta.h"
#include "Cube.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "TextureManager.h"
Porta::Porta(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang)
    : Object(pos, rot, scl, ang) {
    init();
}
Porta::Porta(glm::vec3 pos, float ang)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang) {
    init();
}
void Porta::init() {
    auto& tex = TextureManager::getInstance();
    const float doorW = 0.9f;   
    const float doorH = 2.0f;   
    const float doorT = 0.05f;  
    const float frameT = 0.08f; 
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, doorH, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(doorW + frameT * 2, frameT, frameT),
        0.0f,
        tex.wood2.get()
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-doorW * 0.5f - frameT * 0.5f, doorH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(frameT, doorH, frameT),
        0.0f,
        tex.wood2.get()
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(doorW * 0.5f + frameT * 0.5f, doorH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(frameT, doorH, frameT),
        0.0f,
        tex.wood2.get()
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, doorH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(doorW, doorH, doorT),
        0.0f,
        tex.wood2.get()
    ));
    const float handleHeight = doorH * 0.5f;  
    const float handleXFront = -doorW * 0.35f;  
    const float handleXBack = doorW * 0.35f;    
    const float handleLength = 0.08f;         
    const float handleRadius = 0.035f;        
    const float knobRadius = 0.085f;          
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(handleXFront, handleHeight, doorT * 0.5f + handleLength * 0.5f),
        glm::vec3(1.0f, 0.0f, 0.0f),  
        glm::vec3(handleRadius, handleLength, handleRadius),
        90.0f,           
        36,              
        tex.metal.get()
    ));
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(handleXFront, handleHeight, doorT * 0.5f + handleLength),
        glm::vec3(0.0f),
        glm::vec3(knobRadius),
        0.0f,
        18,              
        36,              
        tex.metal.get()
    ));
    parts.push_back(std::make_unique<Cilindro>(
        glm::vec3(handleXBack, handleHeight, -doorT * 0.5f - handleLength * 0.5f),
        glm::vec3(1.0f, 0.0f, 0.0f),  
        glm::vec3(handleRadius, handleLength, handleRadius),
        90.0f,           
        36,              
        tex.metal.get()
    ));
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(handleXBack, handleHeight, -doorT * 0.5f - handleLength),
        glm::vec3(0.0f),
        glm::vec3(knobRadius),
        0.0f,
        18,              
        36,              
        tex.metal.get()
    ));
}
void Porta::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto& p : parts)
        p->draw(shader, model);
}
