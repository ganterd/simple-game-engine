#pragma once

#include <vector>

#include <sge/utils/export.hpp>
#include <sge/model/aabb.hpp>
#include <sge/model/mesh.hpp>
#include <sge/scene/entity/drawablecomponent.hpp>
#include <sge/model/ModelImporter.hpp>

namespace SGE
{
    class Model : public DrawableComponent
    {
    private:
        std::vector<Mesh*> mMeshes;
        std::vector<Material*> mMaterials;
        AABB mAABB;

    public:
        Model();
        void draw(bool debug = false);
        Export bool loadFromFile(std::string file);
		Export bool loadFromFile(std::string file, float scale, bool makeLeftHanded);
        Export AABB aabb(){ return mAABB; };
    };
}
