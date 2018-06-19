#include "DisplayManager.hpp"

namespace SGE
{
	namespace DisplayManager
	{
		IDisplayManager* init()
		{
			std::string method = ConfigManager::get("display.method");
			std::string sWidth = ConfigManager::get("display.window.width");
			std::string sHeight = ConfigManager::get("display.window.height");
			std::string sXPos = ConfigManager::get("display.window.x");
			std::string sYPos = ConfigManager::get("display.window.y");
			std::string sXRes = ConfigManager::get("display.window.resolution.x");
			std::string sYRes = ConfigManager::get("display.window.resolution.y");
			std::string sFullscreen = ConfigManager::get("display.window.fullscreen");

			int width = atoi(sWidth.c_str());
			int height = atoi(sHeight.c_str());
			int xPos = atoi(sXPos.c_str());
			int yPos = atoi(sYPos.c_str());
			int xRes = atoi(sXRes.c_str());
			int yRes = atoi(sYRes.c_str());
			bool fullScreen = sFullscreen.compare("true") == 0;

			if(width == 0)
				width = DisplayManager::DEFAULT_WIDTH;
			if(height == 0)
				height = DisplayManager::DEFAULT_HEIGHT;
			if(method.compare("SFML") != 0)
				method = DisplayManager::DEFAULT_METHOD;
			if(xPos == 0)
				xPos = DisplayManager::DEFAULT_X_POS;
			if(yPos == 0)
				yPos = DisplayManager::DEFAULT_Y_POS;
			if(xRes == 0)
				xRes = DisplayManager::DEFAULT_X_RES;
			if(yRes == 0)
				yRes = DisplayManager::DEFAULT_Y_RES;

			IDisplayManager* dm;
			if(method == "SFML")
			{
				dm = new SFMLDisplayManager(width, height, xPos, yPos, fullScreen);
				return dm;
			}
			else
			{
				return NULL;
			}
		}
	}
}
