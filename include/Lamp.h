#ifndef LAMP_H
#define LAMP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Lamp : public Object {
public:
    Lamp(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Lamp(glm::vec3 pos, float ang);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
};

#endif // LAMP_H
