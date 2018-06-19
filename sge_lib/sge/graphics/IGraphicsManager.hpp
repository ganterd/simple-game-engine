#ifndef SGE_I_GRAPHICS_MANAGER_HPP
#define SGE_I_GRAPHICS_MANAGER_HPP

#include <sge/display/IDisplayManager.hpp>

namespace SGE
{
	namespace GraphicsManager
	{
		class IGraphicsManager
		{
		protected:
			SGE::IDisplayManager* dm;

		public:
			virtual int init() = 0;
			virtual void clearBuffer() = 0;
		};
	}
}

#endif
