#ifndef SGE_ENTITY_HPP
#define SGE_ENTITY_HPP

#include <vector>
#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "ModelImporter.hpp"

namespace SGE
{
	class Entity
	{
	private:
		std::vector<Mesh*> meshes;
		std::vector<ILight*> lights;
		glm::mat4 modelMat;
		
	public:
		Entity();
		
		bool loadFromFile(std::string file);
		void draw();
		glm::mat4 getModelMat();
		std::vector<ILight*> getLights();
	};
}

#endif
