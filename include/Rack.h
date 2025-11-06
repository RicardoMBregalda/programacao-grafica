#ifndef RACK_H
#define RACK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Texture; // Forward declaration

class Rack : public Object {
public:
    Rack(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* wood = nullptr, Texture* metal = nullptr);
    Rack(glm::vec3 pos, float ang, Texture* wood = nullptr, Texture* metal = nullptr);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* woodTexture;   // Textura de madeira (prateleiras, laterais)
    Texture* metalTexture;  // Textura de metal (pés)
};

#endif // RACK_H
