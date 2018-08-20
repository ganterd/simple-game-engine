#ifndef SGE_OGL_GRAPHICS_MANAGER
#define SGE_OGL_GRAPHICS_MANAGER

#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

#include <easylogging++.h>

#include <sge/graphics/IGraphicsManager.hpp>

namespace SGE
{
	namespace GraphicsManager
	{
		class Export OGLGraphicsManager : public IGraphicsManager
		{
		public:
			OGLGraphicsManager(SGE::IDisplay*);

			int init();

			void clearBuffer();
			static void clearBuffer(const glm::vec4& c);
		};

		#define flushGLErrors() {\
			while(glGetError() != GL_NO_ERROR);\
		}

		#define checkGLErrors() {\
			GLenum err = glGetError();\
			const GLubyte* errString;\
			while(err != GL_NO_ERROR)\
			{\
				errString = gluErrorString(err);\
				LOG(ERROR) << "GL Error: " << errString;\
				err = glGetError();\
			}\
		}
	}
}

#endif
