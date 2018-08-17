#include "OGLGraphicsManager.hpp"

namespace SGE
{
	namespace GraphicsManager
	{
		OGLGraphicsManager::OGLGraphicsManager(SGE::IDisplay* dm)
		{
			this->init();
		}

		int OGLGraphicsManager::init()
		{
			LOG(DEBUG) << "Initialising GL";
			GLenum error = GL_NO_ERROR;

			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();

			error = glGetError();
			if(error != GL_NO_ERROR)
			{
				LOG(FATAL) << " Couldn't initialise GL: " << gluErrorString(error);
				return 0;
			}

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			error = glGetError();
			if(error != GL_NO_ERROR)
			{
				LOG(FATAL) << " Couldn't initialise GL: " << gluErrorString(error);
				return 0;
			}

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			error = glGetError();
			if(error != GL_NO_ERROR)
			{
				LOG(FATAL) << " Couldn't initialise GL: " << gluErrorString(error);
				return 0;
			}

			LOG(DEBUG) << " GL Version:";
			LOG(DEBUG) << " \t" << glGetString(GL_VERSION);

			error = glewInit();
			if(error != GLEW_OK)
			{
				LOG(FATAL) << " Couldn't initialise GLEW: "
					<< glewGetErrorString(error);
				return 0;
			}

			LOG(DEBUG) << " GLEW Version:";
			LOG(DEBUG) << " \t" << glewGetString(GLEW_VERSION);

			return 1;
		}

		void OGLGraphicsManager::clearBuffer()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void OGLGraphicsManager::clearBuffer(const glm::vec4& colour)
		{
			glClearColor(colour.r, colour.g, colour.b, colour.a);
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}
