#include <sge/graphics/material/material.hpp>

 SGE::Material::Material()
 {
     hasNormalMap = false;
     hasOpacityMap = false;
 }

void SGE::Material::addTexture(ITexture* t)
{
    mTextures.push_back(t);
    if(t->type() == ITexture::Type::Normals)
        hasNormalMap = true;
    if(t->type() == ITexture::Type::Opacity)
        hasOpacityMap = true;
};

void SGE::Material::bindAllTextures()
{
    IShader* shader = ShaderManager::getCurrentShader();
    shader->setVariable("hasNormalMap", hasNormalMap);
    shader->setVariable("hasOpacityMap", hasOpacityMap);
    for(int i = 0; i < mTextures.size(); ++i)
    {
        switch(mTextures[i]->type())
        {
        case ITexture::Type::Diffuse:
            mTextures[i]->bindTexture(0);
            break;
        case ITexture::Type::Normals:
            mTextures[i]->bindTexture(1);
            break;
        case ITexture::Type::Opacity:
            mTextures[i]->bindTexture(2);
            break;
        }
    }
}

void SGE::Material::unbindAllTextures()
{
    for(int i = 0; i < mTextures.size(); ++i)
    {
        mTextures[i]->unbindTexture();
    }
}
