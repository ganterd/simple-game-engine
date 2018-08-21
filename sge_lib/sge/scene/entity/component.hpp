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
        std::string mComponentTypeString = "";
        Entity* mEntity = nullptr;
        bool mIsDrawable = false;

    public:
        Export virtual std::string componentTypeString(){ return mComponentTypeString; };
        Export virtual void componentName(const std::string& n){ mComponentName = n; };
        Export virtual std::string componentName(){ return mComponentName; };
        Export virtual bool isDrawable(){ return mIsDrawable; };
        Export virtual void isDrawable(bool b){ mIsDrawable = b; };
        Export virtual void update();
        Export virtual void draw();
        Entity* getEntity(){ return mEntity; };
    };
}
