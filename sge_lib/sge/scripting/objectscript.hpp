#pragma once

namespace SGE
{
    // Forward declaration of entity script
    class Entity;

    class ObjectScript
    {
    public:
        Entity* mEntity;

        virtual void update(){};
    };
}
