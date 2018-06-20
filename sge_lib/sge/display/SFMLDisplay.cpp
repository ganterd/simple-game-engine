#include "SFMLDisplay.hpp"

namespace SGE
{
	SFMLDisplay::SFMLDisplay(int w, int h, int x, int y, bool fullscreen)
	{
		LOG(INFO) << "Initiliasing...";

		//Create window
		sf::ContextSettings settings;
		settings.depthBits         = 24; // Request a 24-bit depth buffer
		settings.stencilBits       = 8;  // Request a 8 bits stencil buffer
		settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing

		window = new sf::RenderWindow(sf::VideoMode(w, h), "Window", sf::Style::Close, settings);
		if( window == NULL )
			LOG(FATAL) << "Window could not be created";

		mWindowSize.width = w;
		mWindowSize.height = h;

		quit = false;
		//this->createGLContext();
	}

	bool SFMLDisplay::createGLContext()
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

	void SFMLDisplay::setAsTarget()
	{
		//SDL_GL_MakeCurrent(this->window, glContext);
	}

	void SFMLDisplay::handleEvents()
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

	void SFMLDisplay::swapBuffers()
	{
		window->display();
	}

	void SFMLDisplay::exit()
	{
		LOG(INFO) << "Quitting";
		window->close();
		delete window;
	}

	bool SFMLDisplay::wasQuitRequested()
	{
		return this->quit;
	}

	// Callback functions
	// ----------------------------------------------------------------
	void SFMLDisplay::onResize(void (*func)(Size))
	{
	}
}
