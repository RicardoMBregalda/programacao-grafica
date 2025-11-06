#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Object.h>
#include <vector>

class Texture;  // Forward declaration

class Esfera : public Object {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    float angle;
    Texture* texture;  // Ponteiro para textura opcional

    Esfera(glm::vec3 pos = glm::vec3(0.0f),
           glm::vec3 rot = glm::vec3(0.0f),
           glm::vec3 scl = glm::vec3(1.0f),
           float ang = 0.0f,
           int stacks = 18,
           int sectors = 36,
           Texture* tex = nullptr);

    void draw(Shader &shader, glm::mat4 model);
    void setTexture(Texture* tex);
    ~Esfera();

private:
    unsigned int VAO, VBO, EBO;
    int stacks;
    int sectors;
    int indexCount;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    void init();
    void generateVertices();
};
