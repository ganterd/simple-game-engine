#include "OGLGraphicsManager.hpp"

namespace SGE
{
	namespace GraphicsManager
	{
		OGLGraphicsManager::OGLGraphicsManager(DisplayManager::IDisplayManager* dm)
		{
			this->init();
		}
		
		int OGLGraphicsManager::init()
		{
			LOG(INFO) << " Initialising";
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
			
			LOG(INFO) << " GL Version:";
			LOG(INFO) << " \t" << glGetString(GL_VERSION);
				
			error = glewInit();
			if(error != GLEW_OK)
			{
				LOG(FATAL) << " Couldn't initialise GLEW: "
					<< glewGetErrorString(error);
				return 0;
			}
			
			LOG(INFO) << " GLEW Version:";
			LOG(INFO) << " \t" << glewGetString(GLEW_VERSION);
			
			return 1;			
		}
		
		void OGLGraphicsManager::clearBuffer()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}
