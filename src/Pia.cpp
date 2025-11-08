#include "Pia.h"
#include "Cube.h"
#include "Texture.h"
Pia::Pia(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, 
         Texture* wood, Texture* ceramic, Texture* plastic)
    : Object(pos, rot, scl, ang), woodTexture(wood), ceramicTexture(ceramic), plasticTexture(plastic) {
    init();
}
Pia::Pia(glm::vec3 pos, float ang, Texture* wood, Texture* ceramic, Texture* plastic)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), 
      woodTexture(wood), ceramicTexture(ceramic), plasticTexture(plastic) {
    init();
}
void Pia::init() {
    const float cabinetW = 0.80f;    
    const float cabinetH = 0.85f;    
    const float cabinetD = 0.55f;    
    const float doorW = cabinetW * 0.48f; 
    const float doorH = cabinetH * 0.75f; 
    const float doorThick = 0.03f;   
    const float sinkW = 0.50f;       
    const float sinkD = 0.40f;       
    const float sinkDepth = 0.15f;   
    const float wallThick = 0.03f;   
    
    // Armário/gabinete da pia
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, cabinetH * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(cabinetW, cabinetH, cabinetD),
        0.0f,
        woodTexture
    ));
    
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
    
    const float handleW = 0.015f;
    const float handleH = 0.08f;
    const float handleZ = doorZ + doorThick * 0.5f + handleW * 0.5f;
    
    // Puxador porta esquerda
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-cabinetW * 0.15f, doorY, handleZ),
        glm::vec3(0.0f),
        glm::vec3(handleW, handleH, handleW),
        0.0f,
        plasticTexture
    ));
    
    // Puxador porta direita
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(cabinetW * 0.15f, doorY, handleZ),
        glm::vec3(0.0f),
        glm::vec3(handleW, handleH, handleW),
        0.0f,
        plasticTexture
    ));
    
    const float sinkBaseY = cabinetH;
    
    // Base da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, sinkBaseY + wallThick * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(sinkW, wallThick, sinkD),
        0.0f,
        ceramicTexture
    ));
    
    // Parede frontal da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, sinkBaseY + sinkDepth * 0.5f, sinkD * 0.5f - wallThick * 0.5f),
        glm::vec3(0.0f),
        glm::vec3(sinkW, sinkDepth, wallThick),
        0.0f,
        ceramicTexture
    ));
    
    // Parede traseira da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, sinkBaseY + sinkDepth * 0.5f, -sinkD * 0.5f + wallThick * 0.5f),
        glm::vec3(0.0f),
        glm::vec3(sinkW, sinkDepth, wallThick),
        0.0f,
        ceramicTexture
    ));
    
    // Parede esquerda da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-sinkW * 0.5f + wallThick * 0.5f, sinkBaseY + sinkDepth * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, sinkDepth, sinkD),
        0.0f,
        ceramicTexture
    ));
    
    // Parede direita da cuba
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(sinkW * 0.5f - wallThick * 0.5f, sinkBaseY + sinkDepth * 0.5f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(wallThick, sinkDepth, sinkD),
        0.0f,
        ceramicTexture
    ));
    const float faucetY = cabinetH + sinkDepth;
    const float faucetZ = -sinkD * 0.47f; 
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, faucetY + 0.15f, faucetZ),
        glm::vec3(0.0f),
        glm::vec3(0.04f, 0.30f, 0.04f),
        0.0f,
        plasticTexture
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, faucetY + 0.20f, faucetZ + 0.08f),
        glm::vec3(0.0f),
        glm::vec3(0.03f, 0.03f, 0.12f),
        0.0f,
        plasticTexture
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-0.06f, faucetY + 0.02f, faucetZ),
        glm::vec3(0.0f),
        glm::vec3(0.025f, 0.05f, 0.025f),
        0.0f,
        plasticTexture
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.06f, faucetY + 0.02f, faucetZ),
        glm::vec3(0.0f),
        glm::vec3(0.025f, 0.05f, 0.025f),
        0.0f,
        plasticTexture
    ));
}
void Pia::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    for (auto &p : parts)
        p->draw(shader, model);
}
