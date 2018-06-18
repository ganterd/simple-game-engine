#include "Entity.hpp"

namespace SGE
{
	Entity::Entity()
	{
		this->modelMat = glm::mat4(1.0f);
	}
	
	bool Entity::loadFromFile(std::string file)
	{
		ModelImporter* importer = new ModelImporter();
		importer->importModel(file);
		this->meshes = importer->getMeshes();
		this->lights = importer->getLights();
	}
	
	void Entity::draw()
	{
		for(int i = 0; i < this->meshes.size(); ++i)
		{
			this->meshes[i]->renderGL();
		}
	}
	
	glm::mat4 Entity::getModelMat()
	{
		return this->modelMat;
	}
	
	std::vector<ILight*> Entity::getLights()
	{
		return this->lights;
	}
}
