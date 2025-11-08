#include "Chuveiro.h"
#include <glm/gtc/matrix_transform.hpp>

Chuveiro::Chuveiro(glm::vec3 pos, float ang, Texture* metalTexture)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang),
      metalTexture(metalTexture),
      tubo(nullptr), braco(nullptr), pescoco(nullptr), cabeca(nullptr)
{
    init();
}

void Chuveiro::init() {
    // Tubo vertical principal
    tubo = new Cilindro(
        glm::vec3(0.0f, 1.4f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.03f, 1.0f, 0.03f),
        0.0f,
        32,
        metalTexture
    );

    // Braço horizontal superior
    braco = new Cilindro(
        glm::vec3(-0.1f, 1.9f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.02f, 0.25f, 0.02f),
        90.0f,
        32,
        metalTexture
    );

    // Pescoco curvado pra baixo
    pescoco = new Cilindro(
        glm::vec3(-0.2f, 1.85f, 0.0f),
        glm::vec3(45.0f, 0.0f, 0.0f),
        glm::vec3(0.015f, 0.1f, 0.015f),
        0.0f,
        32,
        metalTexture
    );

    // Cabeça do chuveiro
    cabeca = new Cilindro(
        glm::vec3(-0.2f, 1.80f, 0.0f),
        glm::vec3(90.0f, 0.0f, 0.0f),
        glm::vec3(0.12f, 0.02f, 0.12f),
        0.0f,
        32,
        metalTexture
    );
}

void Chuveiro::draw(Shader& shader, glm::mat4 parentTransform) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
    model = glm::scale(model, scale);
    glm::mat4 transform = parentTransform * model;

    if (tubo) tubo->draw(shader, transform);
    if (braco) braco->draw(shader, transform);
    if (pescoco) pescoco->draw(shader, transform);
    if (cabeca) cabeca->draw(shader, transform);
}

Chuveiro::~Chuveiro() {
    delete tubo;
    delete braco;
    delete pescoco;
    delete cabeca;
}
