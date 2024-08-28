#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    Vec2 topLeftCorner, dimensions;

    Rect();
    Rect(double x, double y, double w, double h);
    Rect(Vec2 topLeftCorner, Vec2 dimensions);

    Vec2 GetCenter();
    void SetCenter(Vec2 pos);

    bool Contains(Vec2 point);
};

#endif
