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
}

void SGE::Material::bindAllTextures()
{
    Shader* shader = ShaderManager::getCurrentShader();
    shader->setVariable("hasNormalMap", hasNormalMap);
    shader->setVariable("hasOpacityMap", hasOpacityMap);
    for(unsigned int i = 0; i < mTextures.size(); ++i)
    {
        switch(mTextures[i]->type())
        {
        case ITexture::Type::Diffuse:
            shader->setVariable("albedoTexture", 0);
            mTextures[i]->bindTexture(0);
            break;
        case ITexture::Type::Specular:
            shader->setVariable("specularTexture", 1);
            mTextures[i]->bindTexture(1);
            break;
        case ITexture::Type::Normals:
            shader->setVariable("normalsTexture", 2);
            mTextures[i]->bindTexture(2);
            break;
        case ITexture::Type::Opacity:
            shader->setVariable("opacityTexture", 3);
            mTextures[i]->bindTexture(3);
            break;
        default:
            LOG_N_TIMES(1, WARNING) << "Tried to bind and unknown texture type";
        }
    }
}

void SGE::Material::unbindAllTextures()
{
    for(unsigned int i = 0; i < mTextures.size(); ++i)
    {
        mTextures[i]->unbindTexture();
    }
}
