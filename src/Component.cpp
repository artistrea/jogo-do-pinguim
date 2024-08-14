#include "GameObject.h"
#include <string>

Component::Component(GameObject& associated):
    associated(associated), started(false) {}

Component::~Component() {}

void Component::Start() {
    if (this->started) return;

    started = true;
}
