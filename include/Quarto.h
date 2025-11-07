#ifndef QUARTO_H
#define QUARTO_H

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
class Bed;
class Nightstand;
class Lamp;
class Wardrobe;

class Quarto : public Object {
private:
    // Texturas
    Texture* woodTexture;
    Texture* fabricTexture;         // Tecido para colchão
    Texture* pillowFabricTexture;   // Tecido para travesseiros
    Texture* metalTexture;
    Texture* bulbTexture;
    Texture* wallTexture;
    Texture* floorTexture;

    // Componentes do quarto
    std::vector<std::unique_ptr<Object>> components;

    void createRoom();
    void createFurniture();

public:
    Quarto(glm::vec3 pos, float ang,
           Texture* woodTex = nullptr, 
           Texture* fabricTex = nullptr,
           Texture* pillowFabricTex = nullptr,
           Texture* metalTex = nullptr,
           Texture* bulbTex = nullptr,
           Texture* wallTex = nullptr,
           Texture* floorTex = nullptr);

    void init();
    void draw(Shader& shader, glm::mat4 parentTransform) override;
};

#endif // QUARTO_H