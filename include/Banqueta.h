#pragma once
#include "Object.h"
#include <vector>
#include <memory>

class Texture; // Forward declaration

class Banqueta : public Object {
private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* fabricTexture;  // Textura de tecido (assento estofado)
    Texture* metalTexture;   // Textura de metal (haste, base)
    Texture* plasticTexture; // Textura de plástico (rodinhas)
    void init();

public:
    Banqueta(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* fabric = nullptr, Texture* metal = nullptr, Texture* plastic = nullptr);
    Banqueta(glm::vec3 pos, float ang, Texture* fabric = nullptr, Texture* metal = nullptr, Texture* plastic = nullptr);
    
    void draw(Shader &shader, glm::mat4 model) override;
};
