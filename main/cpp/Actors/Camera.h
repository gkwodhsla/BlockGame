#include "HActor.h"

class Camera2DComponent;

class Camera: public HActor
{
public:
    Camera();
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
    virtual ~Camera();
private:
    Camera2DComponent* cameraComp;
};
