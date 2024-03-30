
#include "Sprite.h"
#include "TileSet.h"
#include "GameObject.h"
#include "ThrowError.h"
#include <math.h>

TileSet::TileSet(
    int tileWidth,
    int tileHeight,
    const char* file
) {
    if (tileHeight <= 0 || tileWidth <= 0) ThrowError::Error("TileSet cannot have dimension <= 0");

    GameObject* gameObj = new GameObject();
    tileSet = new Sprite(*gameObj, file);

    gameObj->AddComponent(
        tileSet
    );

    columns = tileSet->GetWidth() / tileWidth;
    rows = tileSet->GetHeight() / tileHeight;
}

TileSet::~TileSet() {
    
}

void TileSet::RenderTile(
    unsigned int index,
    double x,
    double y
) {
    unsigned int tileX = index % columns;
    unsigned int tileY = index / columns;

    if (tileY >= rows) {
        char buff[120];
        snprintf(buff, sizeof(buff),
            "Tried to render tile (%d, %d), but the tileSet dimension is: (%d, %d)", tileX, tileY, rows, columns
        );
        ThrowError::Error(buff);
    }

    tileSet->SetClip(
        tileX * tileWidth,
        tileY * tileHeight,
        tileWidth,
        tileHeight
    );

    tileSet->Render(
        tileX,
        tileY
    );
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}
