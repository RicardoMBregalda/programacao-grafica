#ifndef TV_H
#define TV_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>

class Texture; // Forward declaration

class TV : public Object {
public:
    TV(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* screen = nullptr, Texture* frame = nullptr);
    TV(glm::vec3 pos, float ang, Texture* screen = nullptr, Texture* frame = nullptr);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* screenTexture;  // Textura da tela (preta/azul)
    Texture* frameTexture;   // Textura da moldura (plástico/metal)
};

#endif // TV_H
