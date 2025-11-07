#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Object.h>
class Texture; 
class Prisma : public Object {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    float angle;
    Prisma(glm::vec3 pos = glm::vec3(0.0f),
         glm::vec3 rot = glm::vec3(0.0f),
         glm::vec3 scl = glm::vec3(1.0f),
         float ang = 0.0f,
         Texture* tex = nullptr);
    void draw(Shader &shader, glm::mat4 model);
    void setTexture(Texture* tex);
private:
    unsigned int VAO, VBO, EBO;
    Texture* texture;  
    void init();
};
