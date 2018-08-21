#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include <sge/input/input.hpp>
#include <sge/time/time.hpp>
#include <sge/scene/camera.hpp>
#include <sge/scripting/objectscript.hpp>

class CameraControl : public SGE::ObjectScript
{
public:
    const float accelerationPerSecond = 4.0f;
    const float maxSpeedPerSecond = 4.0f;
    const float decelerationPercentPerSecond = 0.999f;
    const float mouseScale = 0.05f;

    glm::vec3 mCurrentVelocity;

    CameraControl();
    void update();
};
