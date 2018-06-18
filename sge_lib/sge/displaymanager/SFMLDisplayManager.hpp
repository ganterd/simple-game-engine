#ifndef SGE_SDL_DISPLAY_MANAGER_HPP
#define SGE_SDL_DISPLAY_MANAHER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sge/displaymanager/IDisplayManager.hpp>

#include <easylogging++.h>

namespace SGE
{
	namespace DisplayManager
	{
		class SFMLDisplayManager: public IDisplayManager
		{
		private:
			sf::RenderWindow* window;
			
			bool quit;
			
		public:		
			//static SDL_GLContext glContext;
			
			SFMLDisplayManager(int w, int h, int x, int y, bool fullscreen);
			
			bool createGLContext();
			void setAsTarget();
			void handleEvents();
			void swapBuffers();
			void exit();
			
			bool wasQuitRequested();
		
			// Callback functions
			// --------------------------------------------------------------
			void onResize(void (*func)(Size));
		};
	}
}

#endif
