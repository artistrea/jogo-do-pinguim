#ifndef TILE_SET_H
#define TILE_SET_H

#include "Sprite.h"
#include <string>

class TileSet {
public:
    TileSet(
        int tileWidth,
        int tileHeight,
        std::string file
    );
    ~TileSet();
    void RenderTile(
        int index,
        double x,
        double y
    );
    int GetTileWidth();
    int GetTileHeight();

private:
    Sprite* tileSet;
    int rows, columns,
        tileWidth, tileHeight;
};

#endif
