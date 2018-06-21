#pragma once

#include <vector>

#include <sge/graphics/texture/ITexture.hpp>

namespace SGE
{
    class Material
    {
    private:
        std::vector<ITexture*> mTextures;

    public:
        void addTexture(ITexture* t){ mTextures.push_back(t); };
        int numTextures(){ return (int)mTextures.size(); };

        void bindAllTextures();
        void bindTexture(int t);
    };
}
