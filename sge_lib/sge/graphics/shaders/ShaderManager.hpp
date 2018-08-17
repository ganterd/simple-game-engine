#ifndef SGE_SHADER_MANAGER_HPP
#define SGE_SHADER_MANAGER_HPP

#include <string>
#include <map>

#include <sge/graphics/shaders/Shader.hpp>
#include <sge/graphics/shaders/GLSLShader.hpp>

namespace SGE
{
	class ShaderManager
	{
	private:
		static std::map<std::string, Shader*> shaders;
		static int targetBufferWidth;
		static int targetBufferHeight;

	public:
		Export static Shader* currentShader;

		Export static void init();
		Export static void addShader(std::string shaderName, Shader* shader);
		Export static bool hasShader(std::string shader);
		Export static Shader* getShader(std::string shader);
		Export static void setCurrentShader(Shader* shader);
		Export static Shader* getCurrentShader();
		
		Export static SubShader* getCurrentSubShader();

		Export static Shader* useShader(std::string shader);
		Export static SubShader* useShader(std::string shader, std::string subShader);

		Export static void setTargetBufferDimensions(int w, int h);
		Export static int getTargetBufferWidth();
		Export static int getTargetBufferHeight();
	};
}

#endif
