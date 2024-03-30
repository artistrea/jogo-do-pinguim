#ifndef TILE_SET_H
#define TILE_SET_H

#include "Sprite.h"

class TileSet {
public:
    TileSet(
        int tileWidth,
        int tileHeight,
        const char* file
    );
    ~TileSet();
    void RenderTile(
        unsigned int index,
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
