#ifndef SGE_OGL_GRAPHICS_MANAGER
#define SGE_OGL_GRAPHICS_MANAGER

#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>

#include <easylogging++.h>

#include <sge/graphics/IGraphicsManager.hpp>

namespace SGE
{
	namespace GraphicsManager
	{
		class OGLGraphicsManager: public IGraphicsManager
		{
		public:
			OGLGraphicsManager(DisplayManager::IDisplayManager*);
			int init();
			void clearBuffer();
		};
	}
}

#endif
