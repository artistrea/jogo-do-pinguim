#ifndef VEC2_H
#define VEC2_H

#include <ostream>

class Vec2 {
public:
    double x, y;

    Vec2();
    Vec2(double x, double y);
    Vec2(const Vec2& v);

// http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
    Vec2& operator=(const Vec2 &r);
    // bool operator==(const Vec2 &v) const;

    const Vec2 operator+(const Vec2& vec) const;
    Vec2& operator+=(const Vec2& v);

    const Vec2 operator*(const double &scalar) const;
    const Vec2 operator/(const double &scalar) const;
    Vec2& operator*=(const double &scalar);
    Vec2& operator/=(const double &scalar);

    double GetAbs() const;
    double GetAbs();
    Vec2 GetNormalized();

    Vec2 GetRotated(double degInRad);
    double GetRotation() const;
};

std::ostream & operator<<(std::ostream &os, Vec2 const &v);

#endif
