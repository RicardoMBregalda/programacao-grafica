// Prisma.cpp
#include "Prisma.h"

float vertices2[] = {
    // Posi��es          // Coords Textura
    0.0f, 0.0f, 0.0f,    0.0f, 0.0f, // 0 - base esquerda traseira
    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, // 1 - topo traseiro
    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, // 2 - base direita traseira
    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, // 3 - base esquerda frente
    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, // 4 - topo frente
    1.0f, 0.0f, 1.0f,    1.0f, 0.0f  // 5 - base direita frente
};

unsigned int indices2[] = {
    // Face triangular traseira
    0, 1, 2,

    // Face retangular inferior
    0, 2, 5,
    5, 3, 0,

    // Face retangular lateral esquerda
    0, 3, 4,
    4, 1, 0,

    // Face retangular lateral direita (hipotenusa)
    2, 1, 4,
    4, 5, 2,

    // Face triangular frontal
    3, 5, 4
};

Prisma::Prisma(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : position(pos), rotation(rot), scale(scl), angle(angle) {
    init();
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

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // tex coords
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

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
