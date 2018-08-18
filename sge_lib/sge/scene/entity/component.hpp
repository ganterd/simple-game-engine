#pragma once

#include <string>

#include <sge/utils/export.hpp>

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
        Export virtual bool isDrawable(){ return mIsDrawable; };
        Export virtual void isDrawable(bool b){ mIsDrawable = b; };
        Export virtual void update();
        Export virtual void draw();
        Entity* getEntity(){ return mEntity; };
    };
}
