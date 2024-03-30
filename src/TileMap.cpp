#include "TileMap.h"
#include <fstream>
#include "ThrowError.h"
#include <limits>
#include <ios>

TileMap::TileMap(
    GameObject& associated,
    const char* file,
    TileSet* tileSet
): Component(associated) {
    Load(file);
    this->tileSet=nullptr;
    SetTileSet(tileSet);
}

TileMap::~TileMap() {
    delete this->tileSet;
}

void TileMap::Load(const char* file) {
    // read file
    std::ifstream f;
    f.open(file);
    if (!f.is_open()) {
        char buff[90];
        snprintf(buff, sizeof(buff),
            "Failed opening file for TileMap::Load: %s", file
        );
        ThrowError::Error(buff);
    }

    // set dimensions
    f >> mapWidth;
    f.ignore(1, ',');
    f >> mapHeight;
    f.ignore(1, ',');
    f >> mapDepth;
    f.ignore(1, ',');

    // SDL_Log("(%d, %d, %d)", mapWidth, mapHeight, mapDepth);

    tileMatrix.reserve(mapWidth * mapHeight * mapDepth);

    for (int i=0; i < mapDepth; i++) {
        for (int j=0; j < mapHeight; j++) {
            for (int k=0; k < mapWidth; k++) {
                f >> At(k,j,i);
                At(k,j,i)--;
                // SDL_Log("(%d, %d, %d) = %d", k, j, i, At(k,j,i));
                f.ignore(1, ',');

                // f >> tileMatrix[i*mapHeight*mapWidth + j*mapWidth + k];
                // tileMatrix[i*mapHeight*mapWidth + j*mapWidth + k]--;
            }
            f.ignore(1, '\n');
        }
        f.ignore(1, '\n');
    }
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[z*mapHeight*mapWidth + y*mapWidth + x];
}

void TileMap::Render() {
    RenderLayer(
        0,
        associated.box.topLeftCorner.x,
        associated.box.topLeftCorner.y
    );
}

void TileMap::RenderLayer(
    int layer,
    double cameraX,
    double cameraY
) {
    for (int i=0; i < mapHeight; i++) {
        for (int j=0; j < mapWidth; j++) {
            if (At(j, i, layer) == -1) continue;
            // if (j == 0 && i == 0)
            //     SDL_Log("Rendering tile at (%d, %d, %d) = %d", j, i, layer, At(j, i, layer));
            tileSet->RenderTile(
                At(j, i, layer),
                tileSet->GetTileWidth()*j,
                tileSet->GetTileHeight()*i
            );
        }
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(double dt) {

}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

