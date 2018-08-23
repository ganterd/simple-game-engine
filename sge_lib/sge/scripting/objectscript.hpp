#pragma once

#include <sge/scene/entity/component.hpp>

namespace SGE
{
    class ObjectScript : public EntityComponent
    {
    public:
        Export ObjectScript();
        
        virtual void update(){};
    };
}
