#include <sge/model/model.hpp>
#include <sge/model/geometry/box.hpp>

namespace SGE
{
    Model::Model()
    {
        mComponentTypeString = "model";
    }

	bool Model::loadFromFile(std::string file)
	{
		return this->loadFromFile(file, 1.0f, false);
	}

	bool Model::loadFromFile(std::string file, float scale,  bool makeLeftHanded)
	{
		ModelImporter* importer = new ModelImporter();
		importer->importModel(file, scale, makeLeftHanded);
		mMeshes = importer->getMeshes();
        for(Mesh* m : mMeshes)
        {
            mAABB += m->aabb();
        }

		mMaterials = importer->getMaterials();

        LOG(DEBUG) << "Model Loaded:";
        LOG(DEBUG) << "|- File [" << file << "]";
        LOG(DEBUG) << "|- AABB "
            << "[" << (mAABB.min)().x << "," << (mAABB.min)().y << "," << (mAABB.min)().z << "]->"
            << "[" << (mAABB.max)().x << "," << (mAABB.max)().y << "," << (mAABB.max)().z << "]";
		return true;
	}

    void Model::draw(bool debug)
    {
        if(debug)
        {
            Box(mAABB).drawLines();
        }
        else
        {
            for(unsigned int i = 0; i < mMeshes.size(); ++i)
        		mMeshes[i]->draw();
        }
    }
}
