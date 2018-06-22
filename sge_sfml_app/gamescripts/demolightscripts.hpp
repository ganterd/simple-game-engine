#pragma once

#include <cmath>

#include <sge/scripting/objectscript.hpp>
#include <sge/time/time.hpp>

class DemoLightsScript : public SGE::ObjectScript
{
public:
    void update()
    {
        mEntity->setPosition(
            sin(SGE::Time::gameTime()) * 2.0f,
            0.0f, 0.0f
        );
    }
};
