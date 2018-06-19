#ifndef SGE_DISPLAY_MANAGER
#define SGE_DISPLAY_MANAGER

#include <sge/display/IDisplayManager.hpp>
#include <sge/display/SFMLDisplayManager.hpp>

namespace SGE
{
	class DisplayManager
	{
	private:
		static SGE::IDisplayManager* m_CurrentDM;
		static SGE::IDisplayManager* init();

	public:
		static SGE::IDisplayManager* getInstance(){
			if(m_CurrentDM == nullptr)
				m_CurrentDM = init();
			return m_CurrentDM;
		}
	};
}

#endif
