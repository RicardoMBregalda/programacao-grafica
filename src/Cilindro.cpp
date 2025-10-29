// Cilindro.cpp
#include "Cilindro.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Cilindro::Cilindro(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, int segs)
    : position(pos), rotation(rot), scale(scl), angle(ang), segments(segs) {
    generateVertices();
    init();
}

Cilindro::~Cilindro() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cilindro::generateVertices() {
    vertices.clear();
    indices.clear();

    float radius = 0.5f;
    float height = 1.0f;
    float halfHeight = height / 2.0f;

    // Vértices do corpo do cilindro
    for (int i = 0; i <= segments; ++i) {
        float theta = (float)i / segments * 2.0f * M_PI;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        float u = (float)i / segments;

        // Vértice superior
        vertices.push_back(x);
        vertices.push_back(halfHeight);
        vertices.push_back(z);
        vertices.push_back(u);
        vertices.push_back(1.0f);

        // Vértice inferior
        vertices.push_back(x);
        vertices.push_back(-halfHeight);
        vertices.push_back(z);
        vertices.push_back(u);
        vertices.push_back(0.0f);
    }

    int bodyVertexCount = (segments + 1) * 2;

    // Centro da tampa superior
    vertices.push_back(0.0f);
    vertices.push_back(halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(0.5f);
    vertices.push_back(0.5f);

    int topCenterIndex = bodyVertexCount;

    // Vértices da borda da tampa superior
    for (int i = 0; i <= segments; ++i) {
        float theta = (float)i / segments * 2.0f * M_PI;
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        vertices.push_back(x);
        vertices.push_back(halfHeight);
        vertices.push_back(z);
        vertices.push_back(0.5f + 0.5f * cos(theta));
        vertices.push_back(0.5f + 0.5f * sin(theta));
    }

    int topStartIndex = topCenterIndex + 1;

    // Centro da tampa inferior
    vertices.push_back(0.0f);
    vertices.push_back(-halfHeight);
    vertices.push_back(0.0f);
    vertices.push_back(0.5f);
    vertices.push_back(0.5f);

    int bottomCenterIndex = topStartIndex + segments + 1;

    // Vértices da borda da tampa inferior
    for (int i = 0; i <= segments; ++i) {
        float theta = (float)i / segments * 2.0f * M_PI;
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        vertices.push_back(x);
        vertices.push_back(-halfHeight);
        vertices.push_back(z);
        vertices.push_back(0.5f + 0.5f * cos(theta));
        vertices.push_back(0.5f + 0.5f * sin(theta));
    }

    int bottomStartIndex = bottomCenterIndex + 1;

    // Índices do corpo
    for (int i = 0; i < segments; ++i) {
        int top1 = i * 2;
        int bottom1 = i * 2 + 1;
        int top2 = (i + 1) * 2;
        int bottom2 = (i + 1) * 2 + 1;

        indices.push_back(top1);
        indices.push_back(bottom1);
        indices.push_back(top2);

        indices.push_back(top2);
        indices.push_back(bottom1);
        indices.push_back(bottom2);
    }

    // Índices da tampa superior
    for (int i = 0; i < segments; ++i) {
        indices.push_back(topCenterIndex);
        indices.push_back(topStartIndex + i);
        indices.push_back(topStartIndex + i + 1);
    }

    // Índices da tampa inferior
    for (int i = 0; i < segments; ++i) {
        indices.push_back(bottomCenterIndex);
        indices.push_back(bottomStartIndex + i + 1);
        indices.push_back(bottomStartIndex + i);
    }

    indexCount = indices.size();
}

void Cilindro::init() {
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

void Cilindro::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
