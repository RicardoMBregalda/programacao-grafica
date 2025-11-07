#pragma once
#include "Object.h"
#include <vector>
#include <memory>
class Texture; 
class Banqueta : public Object {
private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* fabricTexture;  
    Texture* metalTexture;   
    Texture* plasticTexture; 
    void init();
public:
    Banqueta(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* fabric = nullptr, Texture* metal = nullptr, Texture* plastic = nullptr);
    Banqueta(glm::vec3 pos, float ang, Texture* fabric = nullptr, Texture* metal = nullptr, Texture* plastic = nullptr);
    void draw(Shader &shader, glm::mat4 model) override;
};
