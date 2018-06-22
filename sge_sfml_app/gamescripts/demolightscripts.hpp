#pragma once

#include <cmath>

#include <sge/scripting/objectscript.hpp>
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
            sin(SGE::Time::gameTime() + mOffset) * mRadius * (mReverse ? -1.0f : 1.0f),
            0.0f,
            cos(SGE::Time::gameTime() + mOffset) * mRadius
        );
    }
};
