#ifndef BANHEIRO_H
#define BANHEIRO_H

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
class Pia;
class VasoSanitario;

class Banheiro : public Object {
private:
    // Texturas
    Texture* woodTexture;
    Texture* metalTexture;
    Texture* plasticTexture;
    Texture* wallTexture;
    Texture* floorTexture;

    // Componentes do banheiro
    std::vector<std::unique_ptr<Object>> components;

    void createRoom();
    void createFixtures();

public:
    Banheiro(glm::vec3 pos, float ang,
             Texture* woodTex = nullptr, 
             Texture* metalTex = nullptr,
             Texture* plasticTex = nullptr,
             Texture* wallTex = nullptr,
             Texture* floorTex = nullptr);

    void init();
    void draw(Shader& shader, glm::mat4 parentTransform) override;
};

#endif // BANHEIRO_H
