#pragma once

#include <vector>

#include <sge/utils/export.hpp>
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

    public:
        Model();
        void draw();
        Export bool loadFromFile(std::string file);
		Export bool loadFromFile(std::string file, float scale, bool makeLeftHanded);
    };
}
