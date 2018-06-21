#pragma once

#include <sge/utils/export.hpp>
#include <sge/configmanager/ConfigManager.hpp>
#include <sge/graphics/texture/ITexture.hpp>
#include <sge/graphics/texture/GLSLTexture.hpp>

namespace SGE
{
    class TextureFactory
    {
    public:
        Export static ITexture* newTexture();
    };
}
