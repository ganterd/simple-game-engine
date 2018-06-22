#pragma once

#include <vector>

#include <sge/graphics/texture/ITexture.hpp>
#include <sge/graphics/ShaderManager.hpp>

namespace SGE
{
    class Material
    {
    private:
        std::vector<ITexture*> mTextures;

        bool hasNormalMap;
        bool hasOpacityMap;

    public:
        Material();

        void addTexture(ITexture* t);
        int numTextures(){ return (int)mTextures.size(); };

        void bindAllTextures();
        void unbindAllTextures();
    };
}
