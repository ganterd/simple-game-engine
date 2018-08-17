// Local Includes
//---------------------------------------------------
#include <easylogging++.cc>
INITIALIZE_NULL_EASYLOGGINGPP

#include <sge/configmanager/ConfigManager.hpp>
#include <sge/display/DisplayManager.hpp>
#include <sge/scene/scene.hpp>
#include <sge/scene/importer/sceneimporter.hpp>
#include <sge/graphics/shaders/ShaderManager.hpp>
#include <sge/graphics/OGLGraphicsManager.hpp>

#include "gamescripts/cameracontrol.hpp"
#include "gamescripts/demolightscripts.hpp"

// Function Prototypes
//---------------------------------------------------
//Screen dimension constants
const int DEFAULT_SCREEN_WIDTH = 600;
const int DEFAULT_SCREEN_HEIGHT = 600;

using namespace SGE;

SGE::IDisplay* dm;
GraphicsManager::IGraphicsManager* gm;
Scene* scene;
CameraControl* cameraControl;

bool main_loop()
{
	dm->handleEvents();
	if(dm->wasQuitRequested())
	{
		LOG(INFO) << "Quit requested";
		return false;
	}

	scene->update();
	// cameraControl->update();
	scene->getMainCamera()->render();

	return true;
}

void init()
{
	/* Initialise the display manager */
	dm = SGE::DisplayManager::getDisplayInstance();


	/* Initialise the graphics manager */
	gm = new GraphicsManager::OGLGraphicsManager(dm);

	dm->setAsTarget();

	/* Instantiate the scene object */
	scene = SceneManager::loadScene("resources/scenes/test_scene.xml");
	// SceneImporter sceneImporter;
	// scene = sceneImporter.importSceneFromFile("resources/scenes/test_scene.xml");
	// scene->camera->setAspectRatio((float)dm->size().width / (float)dm->size().height);

	cameraControl = new CameraControl();
	scene->getMainCamera()->getEntity()->addComponent(cameraControl);
	// cameraControl->mCamera = scene->getMainCamera();
}

void exit()
{
	dm->exit();
}

int main( int argc, char* args[] )
{
	el::Helpers::setStorage(SGE::Utils::getELStorage());
	el::Configurations conf("resources/logger.conf");
	//el::Loggers::reconfigureLogger("default", conf);
	el::Loggers::reconfigureAllLoggers(conf);

	for (int i = 1; i < argc; ++i)
	{
		std::string arg = args[i];
		if (arg == "-c")
		{
			std::string configFile = args[i + 1];
			ConfigManager::setConfigFile(configFile);
		}
	}
    ConfigManager::init();


	init();
	while(main_loop());

	exit();

	return 0;
}
