#include <sge/display/DisplayManager.hpp>

SGE::IDisplay* SGE::DisplayManager::m_CurrentDisplay = nullptr;

SGE::IDisplay* SGE::DisplayManager::init()
{
	SGE::IDisplay::Method method = SGE::IDisplay::Method::SFML;
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
		width = SGE::IDisplay::DEFAULT_WIDTH;
	if(height == 0)
		height = SGE::IDisplay::DEFAULT_HEIGHT;
	if(xPos == 0)
		xPos = SGE::IDisplay::DEFAULT_X_POS;
	if(yPos == 0)
		yPos = SGE::IDisplay::DEFAULT_Y_POS;
	if(xRes == 0)
		xRes = SGE::IDisplay::DEFAULT_X_RES;
	if(yRes == 0)
		yRes = SGE::IDisplay::DEFAULT_Y_RES;

	SGE::IDisplay* dm;
	if(method == SGE::IDisplay::Method::SFML)
	{
		dm = new SGE::SFMLDisplay(width, height, xPos, yPos, fullScreen);
		return dm;
	}
	else
	{
		return NULL;
	}
}
