#ifndef SGE_DISPLAY_MANAGER
#define SGE_DISPLAY_MANAGER

#include <sge/display/IDisplay.hpp>
#include <sge/display/SFMLDisplay.hpp>

namespace SGE
{
	class Export DisplayManager
	{
	private:
		static SGE::IDisplay* m_CurrentDisplay;
		static SGE::IDisplay* init();

	public:
		static SGE::IDisplay* getDisplayInstance(){
			if(m_CurrentDisplay == nullptr)
				m_CurrentDisplay = init();
			return m_CurrentDisplay;
		}
	};
}

#endif
