// Esfera.cpp
#include "Esfera.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Esfera::Esfera(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, int stks, int scts)
    : position(pos), rotation(rot), scale(scl), angle(ang), stacks(stks), sectors(scts) {
    generateVertices();
    init();
}

Esfera::~Esfera() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Esfera::generateVertices() {
    vertices.clear();
    indices.clear();

    float radius = 0.5f;

    // Gerar vértices
    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = M_PI / 2.0f - i * M_PI / stacks;  // de pi/2 a -pi/2
        float xy = radius * cos(stackAngle);
        float z = radius * sin(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * 2.0f * M_PI / sectors;  // de 0 a 2pi

            // Posição do vértice
            float x = xy * cos(sectorAngle);
            float y = xy * sin(sectorAngle);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // Coordenadas de textura
            float u = (float)j / sectors;
            float v = (float)i / stacks;
            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    // Gerar índices
    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            // Dois triângulos por quad
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    indexCount = indices.size();
}

void Esfera::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // tex coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Esfera::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
