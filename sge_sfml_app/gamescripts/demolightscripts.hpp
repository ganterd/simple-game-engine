#pragma once

#include <cmath>

#include <sge/scripting/objectscript.hpp>
#include <sge/model/ILight.hpp>
#include <sge/time/time.hpp>

class DemoLightsScript : public SGE::ObjectScript
{
public:
    float mRadius;
    bool mReverse;
    float mOffset;

    DemoLightsScript(float radius, bool reverse, float offset)
    {
        mRadius = radius;
        mReverse = reverse;
        mOffset = offset;
    }

    void update()
    {
        mEntity->setPosition(
            -1.7f,
            1.4,
            0.65
        );

        SGE::ILight* light = mEntity->getLight(0);
        light->setColor(glm::vec3(
            1.0f, 1.0f, 1.0f
        ));
        light->setIntensity(3.0f);
    }
};
