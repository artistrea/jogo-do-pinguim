#include "Rect.h"
#include "Vec2.h"
#include "Collision.h"
#include "Constants.h"

#include <algorithm>
#include <cmath>

// Observação: IsColliding espera ângulos em graus!

bool Collision::IsColliding(Rect& a, Rect& b, float angleDegOfA, float angleDegOfB) {
	Vec2 A[] = { Vec2( a.topLeftCorner.x, a.topLeftCorner.y + a.dimensions.y ),
					Vec2( a.topLeftCorner.x + a.dimensions.x, a.topLeftCorner.y + a.dimensions.y ),
					Vec2( a.topLeftCorner.x + a.dimensions.x, a.topLeftCorner.y ),
					Vec2( a.topLeftCorner.x, a.topLeftCorner.y )
				};
	Vec2 B[] = { Vec2( b.topLeftCorner.x, b.topLeftCorner.y + b.dimensions.y ),
					Vec2( b.topLeftCorner.x + b.dimensions.x, b.topLeftCorner.y + b.dimensions.y ),
					Vec2( b.topLeftCorner.x + b.dimensions.x, b.topLeftCorner.y ),
					Vec2( b.topLeftCorner.x, b.topLeftCorner.y )
				};

	for (auto& v : A) {
		v = Rotate(v - a.GetCenter(), angleDegOfA) + a.GetCenter();
	}

	for (auto& v : B) {
		v = Rotate(v - b.GetCenter(), angleDegOfB) + b.GetCenter();
	}

	Vec2 axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

	for (auto& axis : axes) {
		float P[4];

		for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

		float minA = *std::min_element(P, P + 4);
		float maxA = *std::max_element(P, P + 4);

		for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

		float minB = *std::min_element(P, P + 4);
		float maxB = *std::max_element(P, P + 4);

		if (maxA < minB || minA > maxB)
			return false;
	}

	return true;
}


inline float Collision::Mag(const Vec2& p) {
	return std::sqrt(p.x * p.x + p.y * p.y);
}

inline Vec2 Collision::Norm(const Vec2& p) {
	return p * (1.f / Mag(p));
}

inline float Collision::Dot(const Vec2& a, const Vec2& b) {
	return a.x * b.x + a.y * b.y;
}

inline Vec2 Collision::Rotate(const Vec2& p, float angleDeg) {
	float cs = std::cos(angleDeg * PI / 180), sn = std::sin(angleDeg * PI / 180);
	return Vec2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
}

// Aqui estão três operadores que sua classe Vec2 deve precisar, se já não tiver. 
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.topLeftCorner.x, y + rhs.topLeftCorner.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.topLeftCorner.x, y - rhs.topLeftCorner.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }