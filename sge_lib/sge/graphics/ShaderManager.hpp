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
		static IShader* currentShader;
		static std::string shaderFolder;
	
		static void init();
		static void setShaderFolder(std::string folder);
		static IShader* loadShader(std::string shader);
		static bool hasShader(std::string shader);
		static IShader* getShader(std::string shader);
		static IShader* getCurrentShader();
		static void useShader(std::string shader);
		
		static void setTargetBufferDimensions(int w, int h);
		static int getTargetBufferWidth();
		static int getTargetBufferHeight();
	};
}

#endif
