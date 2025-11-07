#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <memory>
#include "Texture.h"
class TextureManager {
private:
    TextureManager() {
        loadAllTextures();
    }
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
    void loadAllTextures() {
        stone = std::make_unique<Texture>("pedra-28.jpg");
        wood = std::make_unique<Texture>("madeira.jpg");
        metal = std::make_unique<Texture>("metal.jpg");
        plastic = std::make_unique<Texture>("plastico.jpg");
        black = std::make_unique<Texture>("black.png");
        fabric = std::make_unique<Texture>("tecido.jpg");
        fabricLight = std::make_unique<Texture>("tecido_claro.jpg");
        wall = std::make_unique<Texture>("wall.jpg");
        floor = std::make_unique<Texture>("floor.jpg");
    }
public:
    std::unique_ptr<Texture> stone;
    std::unique_ptr<Texture> wood;
    std::unique_ptr<Texture> metal;
    std::unique_ptr<Texture> plastic;
    std::unique_ptr<Texture> black;
    std::unique_ptr<Texture> fabric;
    std::unique_ptr<Texture> fabricLight;
    std::unique_ptr<Texture> wall;
    std::unique_ptr<Texture> floor;
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }
    void clear() {
        stone.reset();
        wood.reset();
        metal.reset();
        plastic.reset();
        black.reset();
        fabric.reset();
        fabricLight.reset();
        wall.reset();
        floor.reset();
    }
    ~TextureManager() {
        clear();
    }
};
#endif 
