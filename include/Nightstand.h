#ifndef NIGHTSTAND_H
#define NIGHTSTAND_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Nightstand : public Object {
public:
    Nightstand(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Nightstand(glm::vec3 pos, float ang);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
};

#endif // NIGHTSTAND_H
