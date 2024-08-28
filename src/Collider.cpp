#include "Collider.h"

#include "Constants.h"
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>

void Collider::Render() {
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.topLeftCorner.x, box.topLeftCorner.y) - center).GetRotated( associated.angleDeg/(180/PI) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.topLeftCorner.x + box.dimensions.x, box.topLeftCorner.y) - center).GetRotated( associated.angleDeg/(180/PI) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.topLeftCorner.x + box.dimensions.x, box.topLeftCorner.y + box.dimensions.y) - center).GetRotated( associated.angleDeg/(180/PI) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.topLeftCorner.x, box.topLeftCorner.y + box.dimensions.y) - center).GetRotated( associated.angleDeg/(180/PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
}

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset): Component(associated), scale(scale), offset(offset), box(associated.box) {}

void Collider::Update(double dt) {
    this->box.dimensions.x = this->associated.box.dimensions.x * this->scale.x;
    this->box.dimensions.y = this->associated.box.dimensions.y * this->scale.y;

    this->box.SetCenter(this->associated.box.GetCenter());
    this->box.topLeftCorner += this->offset;
}

bool Collider::Is(std::string type) {
    return "Collider" == type;
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}
