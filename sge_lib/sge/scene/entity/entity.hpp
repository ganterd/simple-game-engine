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
	class Entity
	{
	friend class EntityComponent;
	protected:
		std::vector<Entity*> mChildren;
		Entity* mParent = nullptr;
		std::vector<Mesh*> meshes;
		std::vector<ILight*> lights;
		std::vector<Material*> mMaterials;
		std::vector<ObjectScript*> mAttachedScripts;
		std::vector<EntityComponent*> mComponents;
		glm::mat4 mLocalModelMat;
		glm::mat4 mWorldModelMat;
		glm::vec3 position;
		glm::vec3 mLocalRotation;

		void updateTranslationMatrix();

	public:
		Export Entity();

		Export void addChild(Entity* childEntity);
		Export std::vector<Entity*> getChildren(){ return mChildren; };

		Export void update();
		Export void draw();
		Export void draw(SubShader* shader);

		Export void setPosition(float, float, float);
		Export void setPosition(glm::vec3);
		Export glm::vec3 getPosition();

		Export void setRotation(float x, float y, float z);
		Export void setRotation(const glm::vec3& r);
		Export glm::vec3 getLocalRotation(){ return mLocalRotation; };
		Export void rotate(float x, float y, float z);

		Export glm::mat4 getModelMat();
		Export glm::mat4 getWorldModelMat(){ return mWorldModelMat; };

		Export void addLight(ILight* l);
		Export std::vector<ILight*> getLights();
		Export ILight* getLight(int lightIndex);

		Export void attachScript(ObjectScript* script);
		Export void addComponent(EntityComponent* component);
	};
}

#endif
