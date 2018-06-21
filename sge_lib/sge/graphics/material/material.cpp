#include <sge/graphics/material/material.hpp>

void SGE::Material::bindAllTextures()
{
    for(int i = 0; i < mTextures.size(); ++i)
    {
        if(mTextures[i]->type() == ITexture::Type::Diffuse)
            mTextures[i]->bindTexture(0);
    }
}
