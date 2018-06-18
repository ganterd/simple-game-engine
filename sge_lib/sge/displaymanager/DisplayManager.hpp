#ifndef SGE_DISPLAY_MANAGER
#define SGE_DISPLAY_MANAGER

#include <sge/displaymanager/IDisplayManager.hpp>
#include <sge/displaymanager/SFMLDisplayManager.hpp>

namespace SGE
{
	namespace DisplayManager
	{
		static const std::string DEFAULT_METHOD = "SDL";
		static const int DEFAULT_WIDTH = 600;
		static const int DEFAULT_HEIGHT = 400;
		static const int DEFAULT_X_POS = 50;
		static const int DEFAULT_Y_POS = 50;
		static const int DEFAULT_X_RES = 600;
		static const int DEFAULT_Y_RES = 400;
		static const bool DEFAULT_FULLSCREEN = false;
		IDisplayManager* init();
	}
}

#endif
