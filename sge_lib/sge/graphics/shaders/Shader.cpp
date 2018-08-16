#include <sge/graphics/shaders/Shader.hpp>

namespace SGE
{
    void Shader::addSubShader(std::string subShaderName, SubShader* subShader)
    {
        mSubShaderMap[subShaderName] = subShader;
        mSubShaders.push_back(subShader);
        mCurrentSubShader = nullptr;
    }

    SubShader* Shader::useSubShader(std::string subShader)
    {
        if(mCurrentSubShader)
        {
            mCurrentSubShader->disable();
            mCurrentSubShader = nullptr;
        }

        if(mSubShaderMap.find(subShader) == mSubShaderMap.end())
        {
            LOG(WARNING) << "No sub shader '" << subShader << "'";
            return nullptr;
        }

        mCurrentSubShader = mSubShaderMap[subShader];
        mCurrentSubShader->enable();
        return mCurrentSubShader;
    }

    SubShader* Shader::useSubShader(int subShaderIndex)
    {
        if(mCurrentSubShader)
        {
            mCurrentSubShader->disable();
            mCurrentSubShader = nullptr;
        }

        if(subShaderIndex >= mSubShaders.size())
        {
            LOG(ERROR) << "No sub shader with index [" << subShaderIndex << "]";
            return nullptr;
        }

        mCurrentSubShader = mSubShaders[subShaderIndex];
        mCurrentSubShader->enable();
        return mCurrentSubShader;
    }

    void Shader::disable()
    {
        if(mCurrentSubShader)
        {
            mCurrentSubShader->disable();
            mCurrentSubShader = nullptr;
        }
    }

    void Shader::draw()
    {

    }
}
