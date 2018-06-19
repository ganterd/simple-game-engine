#ifndef SGE_SDL_DISPLAY_MANAGER_HPP
#define SGE_SDL_DISPLAY_MANAHER_HPP

#include <iostream>

#include <easylogging++.h>
#include <SFML/Graphics.hpp>

#include <sge/display/IDisplayManager.hpp>

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
