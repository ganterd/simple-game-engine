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
            sin(SGE::Time::gameTime() + mOffset) * mRadius * (mReverse ? -1.0f : 1.0f),
            (sin((SGE::Time::gameTime() + mOffset * 3) * 0.01f) + 1.0f) * 1.0f,
            cos(SGE::Time::gameTime() + mOffset) * mRadius
        );

        std::vector<SGE::ILight*> lights = mEntity->getComponentsOfType<SGE::ILight>();
        SGE::ILight* light = lights[0];
        light->setColor(glm::vec3(
            (sin((SGE::Time::gameTime() + mOffset) * 0.1f) + 1.0f) * 0.5f,
            (sin((SGE::Time::gameTime() + mOffset * 2) * 0.1f) + 1.0f) * 0.5f,
            (sin((SGE::Time::gameTime() + mOffset * 3) * 0.1f) + 1.0f) * 0.5f
        ));
        light->setIntensity((sin((SGE::Time::gameTime() + mOffset) * 0.01f) + 1.0f) * 0.1f);
    }
};
