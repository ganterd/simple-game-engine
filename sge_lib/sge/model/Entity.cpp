#include "Entity.hpp"

namespace SGE
{
	Entity::Entity()
	{
		this->modelMat = glm::mat4(1.0f);
		mLocalRotation = glm::vec3(0.0f, 0.0f, 0.0f);
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
		mMaterials = importer->getMaterials();

		return true;
	}

	void Entity::attachScript(ObjectScript* script)
	{
		mAttachedScripts.push_back(script);
		script->mEntity = this;
	}

	void Entity::update()
	{
		for(int i = 0; i < mAttachedScripts.size(); ++i)
		{
			mAttachedScripts[i]->update();
		}
	}

	void Entity::draw()
	{
		for(int i = 0; i < this->meshes.size(); ++i)
		{
			this->meshes[i]->renderGL();
		}
	}

	void Entity::draw(IShader* shader, glm::mat4 currentMat)
	{
		currentMat *= modelMat;
		shader->setVariable("modelMatrix", currentMat);
		for(int i = 0; i < this->meshes.size(); ++i)
			this->meshes[i]->renderGL();

		for(int i = 0; i < mChildren.size(); ++i)
			mChildren[i]->draw(shader, currentMat);
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

	void Entity::setRotation(float x, float y, float z)
	{
		std::cout << "Setting Local Roation to " << x << ", " << y << ", " << z << std::endl;
		mLocalRotation = glm::vec3(x, y, z);
		updateTranslationMatrix();
	}

	void Entity::updateTranslationMatrix()
	{
		glm::mat4 mat(1.0f);
		std::cout << "ROTATING " << mLocalRotation.x << ", " << mLocalRotation.y << ", " << mLocalRotation.z << std::endl;
		mat = glm::rotate(mat, mLocalRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, mLocalRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, mLocalRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		mat = glm::translate(mat, position);
		modelMat = mat;
	}

	glm::mat4 Entity::getModelMat()
	{
		return this->modelMat;
	}

	void Entity::addLight(ILight* l)
	{
		l->mParent = this;
		lights.push_back(l);
	}

	std::vector<ILight*> Entity::getLights()
	{
		return this->lights;
	}

	ILight* Entity::getLight(int lightIndex)
	{
		// Not my fault if you index wrong...
		return lights[lightIndex];
	}
}
