#ifndef SGE_OPACITY_TEXTURE_HPP
#define SGE_OPACITY_TEXTURE_HPP

#include "ITexture.hpp"

namespace SGE
{
	class OpacityTexture : public ITexture
	{
	public:
		OpacityTexture();
		
		void bindTexture();
		void unbindTexture();
	};
}

#endif
