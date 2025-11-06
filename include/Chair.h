#ifndef CHAIR_H
#define CHAIR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Texture; // Forward declaration

class Chair : public Object {
public:
    Chair(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood = nullptr, Texture* fabric = nullptr);
    Chair(glm::vec3 pos, float ang, Texture* wood = nullptr, Texture* fabric = nullptr);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* woodTexture;   // Textura de madeira (pernas, encosto)
    Texture* fabricTexture; // Textura de tecido/estofamento (assento)
};

#endif // CHAIR_H
