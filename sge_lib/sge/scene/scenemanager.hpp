#pragma once

#include <sge/scene/scene.hpp>
#include <sge/scene/importer/sceneimporter.hpp>

namespace SGE
{
    class Scene;
    class SceneManager
    {
    private:
        static Scene* mActiveScene;

    public:
        Export static Scene* loadScene(std::string sceneFile);
        Export static void setActiveScene(Scene* s){ mActiveScene = s; };
        Export static Scene* getActiveScene(){ return mActiveScene; };
    };
}
