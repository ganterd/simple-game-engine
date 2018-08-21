#pragma once

#include <sge/graphics/shaders/SubShader.hpp>
#include <sge/scene/geometry/overlayquad.hpp>

namespace SGE
{
    /* Represents a group of shader passes */
    class Shader
    {
    private:
        std::string mName;
        std::vector<SubShader*> mSubShaders; // Sub shaders in order
        std::map<std::string, SubShader*> mSubShaderMap;
        SubShader* mCurrentSubShader;

    public:
        void setName(std::string n){ mName = n; };

        void addSubShader(std::string subShaderName, SubShader* subShader);
        void listSubShaders();

        void draw();

        SubShader* useSubShader(std::string subShader);
        SubShader* useSubShader(unsigned int subShaderIndex);
        SubShader* getSubShader(std::string subShader);
        std::vector<SubShader*> getSubShaders(){ return mSubShaders; };
        void setCurrentSubShader(SubShader* s);
        SubShader* getCurrentSubShader() { return mCurrentSubShader; };

        void disable();
    };
}
