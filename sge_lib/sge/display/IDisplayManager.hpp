#ifndef SGE_I_DISPLAY_MANAGER_HPP
#define SGE_I_DISPLAY_MANAGER_HPP

#include <sge/configmanager/ConfigManager.hpp>
#include <string>

namespace SGE
{
	namespace DisplayManager
	{
		typedef struct{
			int width;
			int height;
		} Size;

		class IDisplayManager
		{
		protected:
			Size _windowSize;

		public:
			virtual void setAsTarget() = 0;
			virtual void handleEvents() = 0;
			virtual void swapBuffers() = 0;
			virtual void exit() = 0;

			Size size(){ return _windowSize; };
			virtual bool wasQuitRequested() = 0;

			// Callback functions
			// -----------------------------------------------------------
			virtual void onResize(void (*func)(Size)) = 0;

			static IDisplayManager* init();
		};
	}
}

#endif
