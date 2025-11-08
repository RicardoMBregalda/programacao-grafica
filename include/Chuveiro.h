#pragma once
#include "Object.h"
#include "Cilindro.h"

class Chuveiro : public Object {
public:
    Chuveiro(glm::vec3 pos, float ang, Texture* metalTexture);
    ~Chuveiro();

    void draw(Shader& shader, glm::mat4 parentTransform) override;

private:
    void init();

    Texture* metalTexture;
    Cilindro* tubo;
    Cilindro* braco;
    Cilindro* pescoco;
    Cilindro* cabeca;
};
