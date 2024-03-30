#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "GameObject.h"
#include "TileSet.h"
#include "Component.h"
#include <vector>

class TileMap : public Component {
public:
    TileMap(
        GameObject& associated,
        const char* file,
        TileSet* tileSet
    );
    ~TileMap();
    void Load(const char* file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void Render();
    void RenderLayer(
        int layer,
        double cameraX = 0.0,
        double cameraY = 0.0
    );
    int GetWidth();
    int GetHeight();
    int GetDepth();

    void Update(double dt);
    bool Is(std::string type);

private:
    std::vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth,
        mapHeight,
        mapDepth;
};

#endif
