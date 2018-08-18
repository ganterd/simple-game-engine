#include <sge/scene/scenemanager.hpp>
#include <sge/scene/scene.hpp>

namespace SGE
{
    Scene* SceneManager::mActiveScene = nullptr;

    Scene* SceneManager::loadScene(std::string sceneFile)
    {
        SceneImporter sceneImporter;
    	Scene* scene = sceneImporter.importSceneFromFile(sceneFile);
        LOG(DEBUG) << "Scene loaded: " << scene;
        setActiveScene(scene);
        return scene;
    }
}
