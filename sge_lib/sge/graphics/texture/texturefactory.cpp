#include <sge/graphics/texture/texturefactory.hpp>

SGE::ITexture* SGE::TextureFactory::newTexture()
{
    // Can handle different APIs in future
    std::string renderer = SGE::ConfigManager::get("display.renderer");
    if(renderer == "GL")
        return new GLSLTexture();
    else
        return new GLSLTexture();
}
