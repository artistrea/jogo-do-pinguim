#include "Component.h"


class CameraFollower : public Component {
public:
    CameraFollower(GameObject& go);
    void Update(double dt);
    void Render();
    bool Is(std::string type);
};