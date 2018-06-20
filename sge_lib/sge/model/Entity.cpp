#include "Entity.hpp"

namespace SGE
{
	Entity::Entity()
	{
		this->modelMat = glm::mat4(1.0f);
	}
	
	bool Entity::loadFromFile(std::string file)
	{
		return this->loadFromFile(file, 1.0f, false);
	}
	
	bool Entity::loadFromFile(std::string file, float scale,  bool makeLeftHanded)
	{
		ModelImporter* importer = new ModelImporter();
		importer->importModel(file, scale, makeLeftHanded);
		this->meshes = importer->getMeshes();
		this->lights = importer->getLights();
		return true;
	}
	
	void Entity::draw()
	{
		for(int i = 0; i < this->meshes.size(); ++i)
		{
			this->meshes[i]->renderGL();
		}
	}
	
	void Entity::setPositionX(float x)
	{
		this->setPosition(glm::vec3(x, this->position.y, this->position.z));
	}
	
	void Entity::setPositionY(float y)
	{
		this->setPosition(glm::vec3(this->position.x, y, this->position.z));
	}
	
	void Entity::setPositionZ(float z)
	{
		this->setPosition(glm::vec3(this->position.x, this->position.y, z));
	}
	
	void Entity::setPosition(float x, float y, float z)
	{
		this->setPosition(glm::vec3(x, y, z));
	}
	
	void Entity::setPosition(glm::vec3 p)
	{
		this->position = p;
		this->updateTranslationMatrix();
	}
	
	glm::vec3 Entity::getPosition()
	{
		return this->position;
	}
	
	void Entity::updateTranslationMatrix()
	{
		// TODO: Rotation & Scale
		glm::mat4 mat = glm::translate(glm::mat4(1.0f), this->position);
		this->modelMat = mat;
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
