// Local Includes
//---------------------------------------------------
#include <easylogging++.cc>
INITIALIZE_NULL_EASYLOGGINGPP

#include <sge/configmanager/ConfigManager.hpp>
#include <sge/display/DisplayManager.hpp>
#include <sge/scene/scene.hpp>
#include <sge/scene/sceneimporter.hpp>
#include <sge/graphics/ShaderManager.hpp>
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

bool quit = false;

void main_loop()
{
	dm->handleEvents();
	quit = dm->wasQuitRequested();
	if(quit)
	{
		LOG(INFO) << "Quit requested";
		return;
	}
	
	dm->setAsTarget();
	gm->clearBuffer();
	ShaderManager::useShader("depth");
	scene->update();
	cameraControl->update();

	cameraControl->mCamera->lookAt(glm::vec3(-1.0f, -0.2f, 0.5f));
	cameraControl->mCamera->setPosition(glm::vec3(1.4f, -0.1f, 2.6f));

	glFinish();
	Timer drawTimer;
	drawTimer.start();
	scene->draw();
	dm->swapBuffers();
	glFinish();
	drawTimer.stop();
	std::cout << "Iteration time: " << drawTimer.getTime() << "s" << std::endl;
}

void init()
{
	/* Initialise the display manager */
	dm = SGE::DisplayManager::getDisplayInstance();

	/* Initialise the graphics manager */
	gm = new GraphicsManager::OGLGraphicsManager(dm);

	/* Instantiate the scene object */
	SceneImporter sceneImporter;
	scene = sceneImporter.importSceneFromFile("resources/scenes/test_rt_scene.xml");
	scene->camera->setAspectRatio((float)dm->size().width / (float)dm->size().height);

	cameraControl = new CameraControl();
	cameraControl->mCamera = scene->camera;

	Entity* keyLightEntity = new Entity();
	ILight* keyLight = new ILight();
	keyLight->setIntensity(1.0f);
	keyLight->setColor(glm::vec3(0.3f, 0.3f, 1.0f));
	keyLightEntity->setPosition(glm::vec3(0.2f, 1.0f, 3.0f));
	keyLightEntity->addLight(keyLight);
	scene->addEntity(keyLightEntity);

	Entity* detailLightEntity = new Entity();
	ILight* detailLight = new ILight();
	detailLightEntity->setPosition(glm::vec3(2.0f, 1.0f, 0.0f));
	detailLight->setIntensity(0.1f);
	detailLight->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	detailLightEntity->addLight(detailLight);
	scene->addEntity(detailLightEntity);

	Entity* backLightEntity = new Entity();
	ILight* backLight = new ILight();
	backLightEntity->setPosition(glm::vec3(-1.9f, 0.8f, 0.0f));
	backLight->setIntensity(1.6f);
	backLight->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	backLightEntity->addLight(backLight);
	scene->addEntity(backLightEntity);


	ShaderManager::loadShader("normals");
	ShaderManager::loadShader("depth");
}

void exit()
{
	dm->exit();
}

int main( int argc, char* args[] )
{
	el::Helpers::setStorage(SGE::Utils::getELStorage());
	el::Configurations conf("resources/logger.conf");
	el::Loggers::reconfigureLogger("default", conf);
	el::Loggers::reconfigureAllLoggers(conf);

	LOG(DEBUG) << "HERE";

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
	while(!quit)
		main_loop();

	exit();

	return 0;
}
