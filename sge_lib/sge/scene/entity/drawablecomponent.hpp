#pragma once

#include <sge/scene/entity/component.hpp>

namespace SGE
{
    class DrawableComponent : public EntityComponent
    {
    public:
        virtual void draw(bool debug = false) = 0;
    };
}
