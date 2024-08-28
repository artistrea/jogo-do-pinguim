#include "Rect.h"
#include <math.h>

Rect::Rect() : topLeftCorner(), dimensions() {}

Rect::Rect(double x, double y, double w, double h) : topLeftCorner(x, y), dimensions(w, h) {}

Rect::Rect(Vec2 tlCorner, Vec2 dim) : topLeftCorner(tlCorner), dimensions(dim) {}

bool Rect::Contains(Vec2 point) {
    double minX = std::min(topLeftCorner.x, topLeftCorner.x + dimensions.x);
    double maxX = std::max(topLeftCorner.x, topLeftCorner.x + dimensions.x);

    double minY = std::min(topLeftCorner.y, topLeftCorner.y + dimensions.y);
    double maxY = std::max(topLeftCorner.y, topLeftCorner.y + dimensions.y);


    return  point.x <= maxX && point.x >= minX &&
            point.y <= maxY && point.y >= minY;
}

Vec2 Rect::GetCenter() {
    return this->topLeftCorner + (this->dimensions / 2);
}

void Rect::SetCenter(Vec2 newCenter) {
    this->topLeftCorner = newCenter - (this->dimensions / 2);
}


// 1, 1
// 3, 3
// 2, 2
