#pragma once
#include "Object.h"
#include <vector>
#include <memory>

class Wardrobe : public Object {
private:
    std::vector<std::unique_ptr<Object>> parts;
    void init();

public:
    Wardrobe(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Wardrobe(glm::vec3 pos, float ang);
    
    void draw(Shader &shader, glm::mat4 model) override;
};
