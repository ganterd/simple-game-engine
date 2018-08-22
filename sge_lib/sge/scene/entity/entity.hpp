#ifndef SGE_ENTITY_HPP
#define SGE_ENTITY_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sge/model/ModelImporter.hpp>

#include <sge/graphics/shaders/ShaderManager.hpp>
#include <sge/scripting/objectscript.hpp>
#include <sge/scene/entity/component.hpp>

namespace SGE
{
	class EntityComponent;
	class DrawableComponent;
	class Entity
	{
	friend class EntityComponent;
	protected:
		std::string mName;
		std::vector<Entity*> mChildren;
		Entity* mParent = nullptr;

		std::vector<EntityComponent*> mComponents;
		std::vector<DrawableComponent*> mDrawableComponents;

		glm::mat4 mLocalModelMat;
		glm::mat4 mWorldModelMat;
		glm::vec3 position;
		glm::vec3 mLocalRotation;

		void updateTranslationMatrix();

	public:
		Export Entity();

		Export void name(const std::string& n){ mName = n; };
		Export std::string name(){ return mName; };

		Export void addChild(Entity* childEntity);
		Export std::vector<Entity*> getChildren(){ return mChildren; };

		Export void update();
		Export void draw();
		Export void draw(Shader* shader, bool debug = false);

		Export void setPosition(float, float, float);
		Export void setPosition(glm::vec3);
		Export glm::vec3 getPosition();

		Export void setRotation(float x, float y, float z);
		Export void setRotation(const glm::vec3& r);
		Export glm::vec3 getLocalRotation(){ return mLocalRotation; };
		Export void rotate(float x, float y, float z);

		Export glm::mat4 getModelMat();
		Export glm::mat4 getWorldModelMat(){ return mWorldModelMat; };

		Export void addComponent(EntityComponent* component);
		Export std::vector<EntityComponent*> getComponents(){ return mComponents; };
		template <typename ComponentType> Export std::vector<ComponentType*> getComponentsOfType()
		{
			std::vector<ComponentType*> compatibleComponents;
			for(EntityComponent* c : mComponents)
			{
				if(ComponentType* p = dynamic_cast<ComponentType*>(c))
				{
					compatibleComponents.push_back(p);
				}
			}
			return compatibleComponents;
		}

	};
}

#endif
