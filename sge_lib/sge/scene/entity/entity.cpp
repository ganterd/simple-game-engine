#include <sge/scene/entity/entity.hpp>
#include <sge/scene/entity/component.hpp>

namespace SGE
{
	Entity::Entity()
	{
		mWorldModelMat = glm::mat4(1.0f);
		mLocalModelMat = glm::mat4(1.0f);
		mLocalRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	void Entity::attachScript(ObjectScript* script)
	{
		mAttachedScripts.push_back(script);
		script->mEntity = this;
	}

	void Entity::addChild(Entity* childEntity)
	{
		mChildren.push_back(childEntity);
		childEntity->mParent = this;
	}

	void Entity::addComponent(EntityComponent* component)
	{
		mComponents.push_back(component);
		component->mEntity = this;
	}

	void Entity::update()
	{
		if(mParent)
			mWorldModelMat = mLocalModelMat * mParent->mWorldModelMat;
		for(EntityComponent* component : mComponents)
			component->update();

		for(Entity* entity : mChildren)
			entity->update();
	}

	void Entity::draw()
	{
		for(unsigned int i = 0; i < this->meshes.size(); ++i)
		{
			this->meshes[i]->renderGL();
		}
	}

	void Entity::draw(SubShader* shader)
	{
		// // std::cout << "Drawing entity" << std::endl;
		shader->setVariable("modelMatrix", mWorldModelMat);
		for(EntityComponent* component : mComponents)
		{
			// // std::cout << "Component " << component << " is " << component->isDrawable() << " drawable" << std::endl;
			if(component->isDrawable())
			{
				component->draw();
			}
		}

		for(unsigned int i = 0; i < mChildren.size(); ++i)
			mChildren[i]->draw(shader);
	}

	void Entity::setPosition(float x, float y, float z)
	{
		setPosition(glm::vec3(x, y, z));
	}

	void Entity::setPosition(glm::vec3 p)
	{
		this->position = p;
		updateTranslationMatrix();
	}

	glm::vec3 Entity::getPosition()
	{
		return this->position;
	}

	void Entity::setRotation(float x, float y, float z)
	{
		mLocalRotation = glm::vec3(x, y, z);
		updateTranslationMatrix();
	}

	void Entity::setRotation(const glm::vec3& r)
	{
		mLocalRotation = r;
		updateTranslationMatrix();
	}

	void Entity::rotate(float x, float y, float z)
	{
		mLocalRotation += glm::vec3(x, y, z);
		updateTranslationMatrix();
	}

	void Entity::updateTranslationMatrix()
	{
		glm::mat4 mat(1.0f);
		mat = glm::rotate(mat, mLocalRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, mLocalRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		mat = glm::rotate(mat, mLocalRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		mat[3].x = position.x;
		mat[3].y = position.y;
		mat[3].z = position.z;
		mLocalModelMat = mat;
	}

	glm::mat4 Entity::getModelMat()
	{
		return mLocalModelMat;
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
