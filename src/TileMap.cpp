#include "Camera.h"
#include "TileMap.h"
#include "Resources.h"
#include "ThrowError.h"
#include <limits>
#include <ios>
#include <string>
#include <fstream>
#include <math.h>

TileMap::TileMap(
    GameObject& associated,
    std::string file,
    TileSet* tileSet
): Component(associated) {
    Load(file);
    this->tileSet=nullptr;
    SetTileSet(tileSet);
}

TileMap::~TileMap() {
    delete this->tileSet;
}

void TileMap::Load(std::string file) {
    // read file
    std::ifstream f;
    f.open(Resources::GetFullPath(file));

    // set dimensions
    f >> mapWidth;
    f.ignore(1, ',');
    f >> mapHeight;
    f.ignore(1, ',');
    f >> mapDepth;
    f.ignore(1, ',');

    // SDL_Log("(%d, %d, %d)", mapWidth, mapHeight, mapDepth);

    tileMatrix.reserve(mapWidth * mapHeight * mapDepth);
    SDL_Log("tileMatrix.size(): %d", tileMatrix.size());

    for (int i=0; i < mapDepth; i++) {
        for (int j=0; j < mapHeight; j++) {
            for (int k=0; k < mapWidth; k++) {
                tileMatrix.push_back(-1);
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
    SDL_Log("tileMatrix.size(): %d", tileMatrix.size());
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[z*mapHeight*mapWidth + y*mapWidth + x];
}

void TileMap::Render() {
    // SDL_Log("layers: %d", layers);
    // SDL_Log("tileMatrix.size()render: %d", tileMatrix.size());
    // SDL_Log("mapHeight: %d", mapHeight);

    for (int z = 0; z < mapDepth; z++) {
        RenderLayer(
            z,
            Camera::pos.x + Camera::pos.x * 0.4 * z,
            Camera::pos.y + Camera::pos.y * 0.4 * z
        );
    }
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
                tileSet->GetTileWidth()*j - cameraX,
                tileSet->GetTileHeight()*i - cameraY
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
    // this->associated.box.topLeftCorner = Camera::pos;
}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

