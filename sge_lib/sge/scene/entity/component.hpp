#pragma once

#include <string>

namespace SGE
{
    class Entity;
    class EntityComponent
    {
    friend class Entity;
    protected:
        std::string mComponentName = "";
        Entity* mEntity = nullptr;
        bool mIsDrawable = false;

    public:
        virtual bool isDrawable(){ return mIsDrawable; };
        virtual void isDrawable(bool b){ mIsDrawable = b; };
        virtual void update();
        virtual void draw();
        Entity* getEntity(){ return mEntity; };
    };
}
