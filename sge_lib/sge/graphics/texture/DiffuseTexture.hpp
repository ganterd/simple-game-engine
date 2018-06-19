#ifndef SGE_DIFFUSE_TEXTURE_HPP
#define SGE_DIFFUSE_TEXTURE_HPP

#include <sge/graphics/texture/ITexture.hpp>

namespace SGE
{
	class DiffuseTexture : public ITexture
	{
	public:
		DiffuseTexture();

		void bindTexture();
		void unbindTexture();
	};
}

#endif
