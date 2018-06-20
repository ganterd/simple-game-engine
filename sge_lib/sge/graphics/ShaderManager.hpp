#ifndef SGE_SHADER_MANAGER_HPP
#define SGE_SHADER_MANAGER_HPP

#include <string>
#include <map>

#include "IShader.hpp"
#include "GLSLShader.hpp"

namespace SGE
{
	class ShaderManager
	{
	private:
		static std::map<std::string, IShader*> shaders;
		static int targetBufferWidth;
		static int targetBufferHeight;
		
	public:
		Export static IShader* currentShader;
		Export static std::string shaderFolder;
	
		Export static void init();
		Export static void setShaderFolder(std::string folder);
		Export static IShader* loadShader(std::string shader);
		Export static bool hasShader(std::string shader);
		Export static IShader* getShader(std::string shader);
		Export static IShader* getCurrentShader();
		Export static void useShader(std::string shader);
		
		Export static void setTargetBufferDimensions(int w, int h);
		Export static int getTargetBufferWidth();
		Export static int getTargetBufferHeight();
	};
}

#endif
