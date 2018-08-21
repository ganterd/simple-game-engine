#include <sge/model/model.hpp>

namespace SGE
{
    Model::Model()
    {
        mIsDrawable = true;
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
		mMaterials = importer->getMaterials();
		return true;
	}

    void Model::draw()
    {
        for(unsigned int i = 0; i < mMeshes.size(); ++i)
			mMeshes[i]->draw();
    }
}
