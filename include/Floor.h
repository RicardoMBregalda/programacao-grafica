#ifndef FLOOR_H
#define FLOOR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Floor : public Object {
public:
    Floor(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Floor(glm::vec3 pos, float ang);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
};

#endif // FLOOR_H
