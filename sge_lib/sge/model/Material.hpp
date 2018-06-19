#ifndef SGE_MATERIAL_HPP
#define SGE_MATERIAL_HPP

#include <vector>

#include "ITexture.hpp"

namespace SGE
{
	class Material
	{
	private:
		std::vector<ITexture*> textures;
		
	public:
		Material();
		
		void addTexture(ITexture* tex);
	};
}

#endif
