#include "SFMLDisplayManager.hpp"

namespace SGE
{
	namespace DisplayManager
	{
		//SDL_GLContext SDLDisplayManager::glContext;
		
		SFMLDisplayManager::SFMLDisplayManager(int w, int h, int x, int y, bool fullscreen)
		{			
			LOG(INFO) << "Initiliasing...";
			
			window = NULL;
	

			//Create window
			window = new sf::RenderWindow(
				sf::VideoMode(w, h),
				"Window"
			);
			if( window == NULL )
			{
				LOG(FATAL) << "Window could not be created";
			}
			this->_windowSize.width = w;
			this->_windowSize.height = h;
			
			quit = false;
			//this->createGLContext();
		}
		
		bool SFMLDisplayManager::createGLContext()
		{
			LOG(INFO) << "Creating GL context...";
			//glContext = SDL_GL_CreateContext(window);
			//if(glContext == NULL)
			//{
			//	LOG(FATAL) << "Couldn't create GL context: " << SDL_GetError();
			//	return false;
			//}
			return true;
		}
		
		void SFMLDisplayManager::setAsTarget()
		{
			//SDL_GL_MakeCurrent(this->window, glContext);
		}
		
		void SFMLDisplayManager::handleEvents()
		{
			sf::Event e;
			while(window->pollEvent(e))
			{
				if(e.type == sf::Event::Closed)
				{
					quit = true;
				}
			}
		}
		
		void SFMLDisplayManager::swapBuffers()
		{
			window->display();
		}
		
		void SFMLDisplayManager::exit()
		{
			LOG(INFO) << "Quitting";
			window->close();
			delete window;
		}
		
		bool SFMLDisplayManager::wasQuitRequested()
		{
			return this->quit;
		}

		// Callback functions
		// ----------------------------------------------------------------
		void SFMLDisplayManager::onResize(void (*func)(Size))
		{
		}
	}
}
