#ifndef WALL_H
#define WALL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Texture; // Forward declaration

class Wall : public Object {
public:
    Wall(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* tex = nullptr);
    Wall(glm::vec3 pos, float ang, Texture* tex = nullptr);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* wallTexture;  // Textura da parede
};

#endif // WALL_H
