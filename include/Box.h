#ifndef BOX_H
#define BOX_H
#include "Object.h"
#include "Texture.h"
#include "Cube.h"
#include <memory>
class Box : public Object {
public:
    Box(glm::vec3 pos, float ang, Texture* glassTexture, Texture* tileTexture);
    void draw(Shader& shader, glm::mat4 parentTransform) override;
    ~Box();
private:
    void init();
    Texture* glassTexture;
    Texture* tileTexture;
    Cube* leftWall;
    Cube* rightWall;
    Cube* door;
    Cube* floor;
};
#endif
