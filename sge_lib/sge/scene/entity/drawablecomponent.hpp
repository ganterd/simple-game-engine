#pragma once

#include <sge/scene/entity/component.hpp>
#include <sge/model/aabb.hpp>

namespace SGE
{
    class DrawableComponent : public EntityComponent
    {
    protected:
        bool mCastsShadows = false;
        AABB mAABB;
    public:

        virtual void castsShadows(bool b){ mCastsShadows = b; };
        virtual bool castsShadows() const { return mCastsShadows; };
        virtual void draw(bool debug = false) = 0;
        Export AABB aabb(){ return mAABB; };
    };
}
