#include "GameObject.h"
#include <string>

Component::Component(GameObject& associated): associated(associated) {}

Component::~Component() {}
