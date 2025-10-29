#ifndef BED_H
#define BED_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Bed : public Object {
public:
    Bed(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Bed(glm::vec3 pos, float ang);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
};

#endif // BED_H
