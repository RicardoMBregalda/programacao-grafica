#ifndef PORTA_H
#define PORTA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Texture;

class Porta : public Object {
private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* woodTexture;
    Texture* metalTexture;

public:
    Porta(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood = nullptr, Texture* metal = nullptr);
    Porta(glm::vec3 pos, float ang, Texture* wood = nullptr, Texture* metal = nullptr);

    void init();
    void draw(Shader& shader, glm::mat4 model) override;
};

#endif
