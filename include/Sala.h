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
class Tapete;
class Prato; 

class Sala : public Object {
private:
    // Texturas
    Texture* woodTexture;
    Texture* metalTexture;
    Texture* plasticTexture;
    Texture* blackTexture;
    Texture* fabricTexture;
    Texture* fabricTexture2;  // Segunda textura de tecido para o tapete
    Texture* stoneTexture;
    Texture* wallTexture;
    Texture* floorTexture;

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
         Texture* fabricTex2 = nullptr,
         Texture* stoneTex = nullptr,
         Texture* wallTex = nullptr,
         Texture* floorTex = nullptr);
    
    Sala(glm::vec3 pos, float ang,
         Texture* woodTex = nullptr, 
         Texture* metalTex = nullptr,
         Texture* plasticTex = nullptr,
         Texture* blackTex = nullptr,
         Texture* fabricTex = nullptr,
         Texture* fabricTex2 = nullptr,
         Texture* stoneTex = nullptr,
         Texture* wallTex = nullptr,
         Texture* floorTex = nullptr);

    void init();
    void draw(Shader& shader, glm::mat4 parentTransform) override;
};

#endif
