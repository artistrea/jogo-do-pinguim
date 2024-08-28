#ifndef COLLISION_H
#define COLLISION_H

#include "Rect.h"
#include "Vec2.h"

class Collision {
public:
    // Observação: IsColliding espera ângulos em radianos!
    // Para usar graus, forneça a sua própria implementação de Rotate,
    // ou transforme os ângulos no corpo de IsColliding.
    static bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB);
private:
    static inline float Mag(const Vec2& p);
    static inline Vec2 Norm(const Vec2& p);
    static inline float Dot(const Vec2& a, const Vec2& b);
    static inline Vec2 Rotate(const Vec2& p, float angle);
};

#endif // COLLISION_H