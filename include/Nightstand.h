#ifndef NIGHTSTAND_H
#define NIGHTSTAND_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Texture; // Forward declaration

class Nightstand : public Object {
public:
    Nightstand(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood = nullptr, Texture* metal = nullptr);
    Nightstand(glm::vec3 pos, float ang, Texture* wood = nullptr, Texture* metal = nullptr);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* woodTexture;   // Textura de madeira (corpo, tampo, gavetas)
    Texture* metalTexture;  // Textura de metal (puxadores)
};

#endif // NIGHTSTAND_H
