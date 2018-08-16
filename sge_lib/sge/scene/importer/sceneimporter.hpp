#ifndef SGE_SCENE_IMPORTER_HPP
#define SGE_SCENE_IMPORTER_HPP

#include <tinyxml2.h>
#include <easylogging++.h>
#include <string>
#include <vector>

#include <sge/scene/scene.hpp>
#include <sge/model/Entity.hpp>
#include <sge/scene/importer/processors.hpp>

namespace SGE
{
	class Export SceneImporter
	{
	private:
		const char* _readFile(const char* filePath);
		std::string _getSceneName(const tinyxml2::XMLElement* root);
		std::vector<Entity*> _getSceneEntities(const tinyxml2::XMLElement* root);
		Entity* _getEntity(const tinyxml2::XMLElement* entityNode);

		void _processModelComponent(const tinyxml2::XMLElement* modelNode, Entity* parentEntity);
		void _processLightComponent(const tinyxml2::XMLElement* modelNode, Entity* parentEntity);

	public:
		Scene* importSceneFromFile(std::string sceneFile);
	};
}

#endif
