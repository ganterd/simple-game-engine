#pragma once

#include <sge/scene/entity/component.hpp>

namespace SGE
{
    class ObjectScript : public EntityComponent
    {
    public:
        ObjectScript();
        
        virtual void update(){};
    };
}
