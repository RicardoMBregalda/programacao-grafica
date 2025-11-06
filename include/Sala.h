#ifndef SALA_H
#define SALA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

// Forward declarations
class Texture;
class Floor;
class Wall;
class Sofa;
class Table;
class Rack;
class TV;
class Chair;

class Sala : public Object {
private:
    // Texturas
    Texture* woodTexture;
    Texture* metalTexture;
    Texture* plasticTexture;
    Texture* blackTexture;
    Texture* fabricTexture;
    Texture* stoneTexture;

    // Componentes da sala
    std::vector<std::unique_ptr<Object>> components;

    void createRoom();
    void createLivingArea();
    void createDiningArea();

public:
    Sala(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang,
         Texture* woodTex = nullptr, 
         Texture* metalTex = nullptr,
         Texture* plasticTex = nullptr,
         Texture* blackTex = nullptr,
         Texture* fabricTex = nullptr,
         Texture* stoneTex = nullptr);
    
    Sala(glm::vec3 pos, float ang,
         Texture* woodTex = nullptr, 
         Texture* metalTex = nullptr,
         Texture* plasticTex = nullptr,
         Texture* blackTex = nullptr,
         Texture* fabricTex = nullptr,
         Texture* stoneTex = nullptr);

    void init();
    void draw(Shader& shader, glm::mat4 parentTransform) override;
};

#endif
