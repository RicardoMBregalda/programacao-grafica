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
        stone = std::make_unique<Texture>("texturas/pedra-28.jpg");
        wood = std::make_unique<Texture>("texturas/madeira.jpg");
        metal = std::make_unique<Texture>("texturas/metal.jpg");
        plastic = std::make_unique<Texture>("texturas/plastico.jpg");
        black = std::make_unique<Texture>("texturas/black.png");
        fabric = std::make_unique<Texture>("texturas/tecido.jpg");
        fabricLight = std::make_unique<Texture>("texturas/tecido_claro.jpg");
        wall = std::make_unique<Texture>("texturas/wall.jpg");
        floor = std::make_unique<Texture>("texturas/floor.jpg");
        tile = std::make_unique<Texture>("texturas/azulejo.png");
        ceramics = std::make_unique<Texture>("texturas/ceramica.jpg");
        bathroomFloor = std::make_unique<Texture>("texturas/chao_banheiro.png");
        sofa = std::make_unique<Texture>("texturas/sofa.png");
        wood2 = std::make_unique<Texture>("texturas/wood2.jpg");
        wood3 = std::make_unique<Texture>("texturas/wood3.png");
        blanket = std::make_unique<Texture>("texturas/colcha.jpg");
        wardrobe = std::make_unique<Texture>("texturas/wardrobe.jpg");
        table = std::make_unique<Texture>("texturas/table.jpg");
        bedframe = std::make_unique<Texture>("texturas/bedframe.jpg");
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
    std::unique_ptr<Texture> tile;
    std::unique_ptr<Texture> ceramics;
    std::unique_ptr<Texture> bathroomFloor;
    std::unique_ptr<Texture> sofa;
    std::unique_ptr<Texture> wood2;
    std::unique_ptr<Texture> wood3;
    std::unique_ptr<Texture> blanket;
    std::unique_ptr<Texture> wardrobe;
    std::unique_ptr<Texture> table;
    std::unique_ptr<Texture> bedframe;
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
        tile.reset();
        ceramics.reset();
        bathroomFloor.reset();
        sofa.reset();
        wood2.reset();
        wood3.reset();
        blanket.reset();
        wardrobe.reset();
        table.reset();
        bedframe.reset();
    }
    ~TextureManager() {
        clear();
    }
};
#endif 
