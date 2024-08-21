#include "Constants.h"
#include "Vec2.h"
#include <math.h>
#include <iostream>
#include <ostream>

Vec2::Vec2(): x(0), y(0) {}

Vec2::Vec2(double x, double y): x(x), y(y) {}

Vec2::Vec2(const Vec2 &v): x(v.x), y(v.y) {}

Vec2& Vec2::operator=(const Vec2 &rhs) {
    // skip assignment if lhs == rhs
    // more important if deallocating memory
    if (this == &rhs)
      return *this;         

    x = rhs.x;
    y = rhs.y;

    return *this;
}

const Vec2 Vec2::operator+(const Vec2& vec)  const {
    Vec2 result(*this);
    result += vec;
    return result;
}

const Vec2 Vec2::operator*(const double& scalar)  const {
    Vec2 result(*this);
    result *= scalar;
    return result;
}

const Vec2 Vec2::operator/(const double& scalar)  const {
    Vec2 result(*this);
    result /= scalar;
    return result;
}


Vec2& Vec2::operator+=(const Vec2 &rhs) {
    x = rhs.x + x;
    y = rhs.y + y;

    return *this;
}

Vec2& Vec2::operator*=(const double& scalar) {
    x = scalar * x;
    y = scalar * y;

    return *this;
}

Vec2& Vec2::operator/=(const double& scalar) {
    x = x / scalar;
    y = y / scalar;

    return *this;
}

// bool Vec2::operator==(const Vec2 &v) const {
//     return x == v.x && y == v.y;
// }

double Vec2::GetAbs() {
    return sqrt(x*x + y*y);
}
double Vec2::GetAbs() const {
    return sqrt(x*x + y*y);
}

Vec2 Vec2::GetNormalized() {
    return (*this) / this->GetAbs();
}

Vec2 Vec2::GetRotated(double degInRad) {
    Vec2 v;
    v.x = x * cos(degInRad) - y * sin(degInRad);
    v.y = y * cos(degInRad) + x * sin(degInRad);

    return v;
}

// returns value in [-PI, PI]
double Vec2::GetRotation() const {
    return std::atan2(this->y, this->x);
}

std::ostream & operator<<(std::ostream &os, Vec2 const &v) {
    os << "Vec2{x: "<< v.x <<", y: "<< v.y << "}";
    return os;
}


