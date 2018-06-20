#ifndef SGE_ENTITY_HPP
#define SGE_ENTITY_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.hpp"
#include "ModelImporter.hpp"

namespace SGE
{
	class Export Entity
	{
	private:
		std::vector<Mesh*> meshes;
		std::vector<ILight*> lights;
		glm::mat4 modelMat;
		glm::vec3 position;
		
		void updateTranslationMatrix();
		
	public:
		Entity();
		
		bool loadFromFile(std::string file);
		bool loadFromFile(std::string file, float scale, bool makeLeftHanded);
		
		void draw();
		
		void setPositionX(float);
		void setPositionY(float);
		void setPositionZ(float);
		void setPosition(float, float, float);
		void setPosition(glm::vec3);
		
		glm::vec3 getPosition();
		
		glm::mat4 getModelMat();
		std::vector<ILight*> getLights();
	};
}

#endif
