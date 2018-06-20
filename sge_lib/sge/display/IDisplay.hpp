#ifndef SGE_I_DISPLAY_MANAGER_HPP
#define SGE_I_DISPLAY_MANAGER_HPP

#include <sge/configmanager/ConfigManager.hpp>
#include <string>

namespace SGE
{
	typedef Export struct{
		int width;
		int height;
	} Size;

	class Export IDisplay
	{
	public:
		enum Method
		{
			SFML // Only SFML for now
		};

		static const Method DEFAULT_METHOD = Method::SFML;
		static const int DEFAULT_WIDTH = 600;
		static const int DEFAULT_HEIGHT = 400;
		static const int DEFAULT_X_POS = 50;
		static const int DEFAULT_Y_POS = 50;
		static const int DEFAULT_X_RES = 600;
		static const int DEFAULT_Y_RES = 400;
		static const bool DEFAULT_FULLSCREEN = false;

		virtual void setAsTarget() = 0;
		virtual void handleEvents() = 0;
		virtual void swapBuffers() = 0;
		virtual void exit() = 0;

		Method getMethod(){ return mMethod; };
		Size size(){ return mWindowSize; };
		virtual bool wasQuitRequested() = 0;

		// Callback functions
		// -----------------------------------------------------------
		virtual void onResize(void (*func)(Size)) = 0;

		static IDisplay* init();

	protected:
		Size mWindowSize;
		Method mMethod;
	};
}

#endif
