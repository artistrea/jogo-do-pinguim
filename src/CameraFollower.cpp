#include "Component.h"
#include "CameraFollower.h"
#include "Camera.h"


CameraFollower::CameraFollower(GameObject& go): Component(go) {}

void CameraFollower::Update(double dt) {
    this->associated.box.topLeftCorner = Camera::pos;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(std::string type) {
    return type == "CameraFollower";
}

