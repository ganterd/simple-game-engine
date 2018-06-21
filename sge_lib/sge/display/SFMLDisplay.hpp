#ifndef SGE_SDL_DISPLAY_MANAGER_HPP
#define SGE_SDL_DISPLAY_MANAHER_HPP

#include <iostream>

#include <easylogging++.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <sge/display/IDisplay.hpp>

namespace SGE
{
	class Export SFMLDisplay : public IDisplay
	{
	friend class SFMLInputHandler;
	private:
		sf::RenderWindow* window;

		bool quit;
		bool hasCursor;

	public:
		SFMLDisplay(int w, int h, int x, int y, bool fullscreen);

		void setAsTarget();
		void handleEvents();
		void swapBuffers();
		void exit();
		void toggleGrabCursor();

		bool wasQuitRequested();

		// Callback functions
		// --------------------------------------------------------------
		void onResize(void (*func)(Size));
	};
}

#endif
