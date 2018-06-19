#include <sge/display/DisplayManager.hpp>

SGE::IDisplayManager* SGE::DisplayManager::m_CurrentDM = nullptr;

SGE::IDisplayManager* SGE::DisplayManager::init()
{
	SGE::IDisplayManager::Method method = SGE::IDisplayManager::Method::SFML;
	std::string sWidth = SGE::ConfigManager::get("display.window.width");
	std::string sHeight = SGE::ConfigManager::get("display.window.height");
	std::string sXPos = SGE::ConfigManager::get("display.window.x");
	std::string sYPos = SGE::ConfigManager::get("display.window.y");
	std::string sXRes = SGE::ConfigManager::get("display.window.resolution.x");
	std::string sYRes = SGE::ConfigManager::get("display.window.resolution.y");
	std::string sFullscreen = SGE::ConfigManager::get("display.window.fullscreen");

	int width = atoi(sWidth.c_str());
	int height = atoi(sHeight.c_str());
	int xPos = atoi(sXPos.c_str());
	int yPos = atoi(sYPos.c_str());
	int xRes = atoi(sXRes.c_str());
	int yRes = atoi(sYRes.c_str());
	bool fullScreen = sFullscreen.compare("true") == 0;

	if(width == 0)
		width = SGE::IDisplayManager::DEFAULT_WIDTH;
	if(height == 0)
		height = SGE::IDisplayManager::DEFAULT_HEIGHT;
	if(xPos == 0)
		xPos = SGE::IDisplayManager::DEFAULT_X_POS;
	if(yPos == 0)
		yPos = SGE::IDisplayManager::DEFAULT_Y_POS;
	if(xRes == 0)
		xRes = SGE::IDisplayManager::DEFAULT_X_RES;
	if(yRes == 0)
		yRes = SGE::IDisplayManager::DEFAULT_Y_RES;

	SGE::IDisplayManager* dm;
	if(method == SGE::IDisplayManager::Method::SFML)
	{
		dm = new SGE::SFMLDisplayManager(width, height, xPos, yPos, fullScreen);
		return dm;
	}
	else
	{
		return NULL;
	}
}
