// Local Includes
//---------------------------------------------------
#include <easylogging++.h>
INITIALIZE_EASYLOGGINGPP

#include <sge/configmanager/ConfigManager.hpp>
#include <sge/display/DisplayManager.hpp>
#include <sge/scene/scene.hpp>
#include <sge/scene/sceneimporter.hpp>
#include <sge/graphics/ShaderManager.hpp>
#include <sge/graphics/OGLGraphicsManager.hpp>

#include "cameracontrol.hpp"

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
	ShaderManager::useShader("normals");
	scene->update();
	cameraControl->update();

	scene->draw();
	dm->swapBuffers();
}

void init()
{
	/* Initialise the display manager */
	dm = SGE::DisplayManager::getDisplayInstance();

	/* Initialise the graphics manager */
	gm = new GraphicsManager::OGLGraphicsManager(dm);

	/* Instantiate the scene object */
	SceneImporter sceneImporter;
	scene = sceneImporter.importSceneFromFile("../../resources/scenes/test_scene.xml");
	scene->camera->setAspectRatio((float)dm->size().width / (float)dm->size().height);

	cameraControl = new CameraControl();
	cameraControl->mCamera = scene->camera;

	ShaderManager::loadShader("normals");
	ShaderManager::loadShader("depth");
}

void exit()
{
	dm->exit();
}

int main( int argc, char* args[] )
{
    el::Configurations conf("../../resources/logger.conf");
    el::Loggers::reconfigureLogger("default", conf);
    el::Loggers::reconfigureAllLoggers(conf);

    ConfigManager::init();

	init();

	while(!quit)
		main_loop();

	exit();

	return 0;
}
