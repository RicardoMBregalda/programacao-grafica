#pragma once
#include "Object.h"
#include <vector>
#include <memory>
class Texture;  
class Wardrobe : public Object {
private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* woodTexture;   
    Texture* metalTexture;  
    void init();
public:
    Wardrobe(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, 
             Texture* wood = nullptr, Texture* metal = nullptr);
    Wardrobe(glm::vec3 pos, float ang, 
             Texture* wood = nullptr, Texture* metal = nullptr);
    void draw(Shader &shader, glm::mat4 model) override;
};
