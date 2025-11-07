#include "Prisma.h"
#include "Texture.h"
float vertices2[] = {
    0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 
    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 
    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 
    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 
    1.0f, 0.0f, 1.0f,    1.0f, 0.0f  
};
unsigned int indices2[] = {
    0, 1, 2,
    0, 2, 5,
    5, 3, 0,
    0, 3, 4,
    4, 1, 0,
    2, 1, 4,
    4, 5, 2,
    3, 5, 4
};
Prisma::Prisma(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle, Texture* tex)
    : position(pos), rotation(rot), scale(scl), angle(angle), texture(tex) {
    init();
}
void Prisma::setTexture(Texture* tex) {
    texture = tex;
}
void Prisma::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}
void Prisma::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    shader.setMat4("model", model);
    if (texture != nullptr) {
        texture->bind(0);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
