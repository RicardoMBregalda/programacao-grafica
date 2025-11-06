#ifndef LAMP_H
#define LAMP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Texture; // Forward declaration

class Lamp : public Object {
public:
    Lamp(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* metal = nullptr, Texture* shade = nullptr, Texture* bulb = nullptr);
    Lamp(glm::vec3 pos, float ang, Texture* metal = nullptr, Texture* shade = nullptr, Texture* bulb = nullptr);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* metalTexture;  // Textura de metal (base, haste, conector)
    Texture* shadeTexture;  // Textura da cúpula/abajur (tecido/plástico)
    Texture* bulbTexture;   // Textura da lâmpada (amarelo/branco)
};

#endif // LAMP_H
