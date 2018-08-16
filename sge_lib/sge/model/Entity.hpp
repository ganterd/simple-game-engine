#ifndef SGE_ENTITY_HPP
#define SGE_ENTITY_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.hpp"
#include "ModelImporter.hpp"

#include <sge/graphics/ShaderManager.hpp>
#include <sge/scripting/objectscript.hpp>

namespace SGE
{
	class Entity
	{
	private:
		std::vector<Entity*> mChildren;
		Entity* mParent = nullptr;
		std::vector<Mesh*> meshes;
		std::vector<ILight*> lights;
		std::vector<Material*> mMaterials;
		std::vector<ObjectScript*> mAttachedScripts;
		glm::mat4 modelMat;
		glm::vec3 position;
		glm::vec3 mLocalRotation;

		void updateTranslationMatrix();

	public:
		Export Entity();

		Export bool loadFromFile(std::string file);
		Export bool loadFromFile(std::string file, float scale, bool makeLeftHanded);

		Export void addChild(Entity* childEntity){ mChildren.push_back(childEntity); };
		Export std::vector<Entity*> getChildren(){ return mChildren; };
		Export void setParent(Entity* parentEntity){ mParent = parentEntity; };

		Export void update();
		Export void draw();
		Export void draw(IShader* shader, glm::mat4 parentMat = glm::mat4(1.0f));

		Export void setPositionX(float);
		Export void setPositionY(float);
		Export void setPositionZ(float);
		Export void setPosition(float, float, float);
		Export void setPosition(glm::vec3);
		Export glm::vec3 getPosition();

		Export void setRotation(float x, float y, float z);

		Export glm::mat4 getModelMat();

		Export void addLight(ILight* l);
		Export std::vector<ILight*> getLights();
		Export ILight* getLight(int lightIndex);

		Export void attachScript(ObjectScript* script);
	};
}

#endif
