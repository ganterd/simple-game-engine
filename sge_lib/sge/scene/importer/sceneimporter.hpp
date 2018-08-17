#ifndef SGE_SCENE_IMPORTER_HPP
#define SGE_SCENE_IMPORTER_HPP

#include <tinyxml2.h>
#include <easylogging++.h>
#include <string>
#include <vector>

#include <sge/scene/scene.hpp>
#include <sge/scene/entity/entity.hpp>
#include <sge/scene/importer/processors.hpp>

namespace SGE
{
	class Scene;
	class Export SceneImporter
	{
	private:
		std::string _getSceneName(const tinyxml2::XMLElement* root);
		std::vector<Entity*> _getSceneEntities(const tinyxml2::XMLElement* root);
		Entity* _getEntity(const tinyxml2::XMLElement* entityNode);

		void processShaders(const tinyxml2::XMLElement* root);

	public:
		Scene* importSceneFromFile(std::string sceneFile);
	};
}

#endif
