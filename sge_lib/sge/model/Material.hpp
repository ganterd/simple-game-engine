#ifndef SGE_MATERIAL_HPP
#define SGE_MATERIAL_HPP

#include <vector>

#include <sge/graphics/texture/ITexture.hpp>

namespace SGE
{
	class Export Material
	{
	private:
		std::vector<ITexture*> textures;
		
	public:
		Material();
		
		void addTexture(ITexture* tex);
	};
}

#endif
