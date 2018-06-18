#include "ShaderManager.hpp"

namespace SGE
{	
	IShader* ShaderManager::currentShader = NULL;
	std::string ShaderManager::shaderFolder = "../../resources/shaders/";
	std::map<std::string, IShader*> ShaderManager::shaders;
	
	void ShaderManager::init()
	{
		setShaderFolder("../../resources/shaders/");
		currentShader = NULL;
	}
	
	void ShaderManager::setShaderFolder(std::string folder)
	{
		shaderFolder = folder;
	}
	
	IShader* ShaderManager::loadShader(std::string shader)
	{
		if(hasShader(shader))
			return getShader(shader);
			
		IShader* s;
		
		/* Should be some logic to determine if using GLSL or HLSL shaders */
		s = new GLSLShader();
		std::string vertShaderFilePath = shaderFolder;
		vertShaderFilePath.append(shader);
		vertShaderFilePath.append(".vert");
		
		std::string fragShaderFilePath = shaderFolder;
		fragShaderFilePath.append(shader);
		fragShaderFilePath.append(".frag");
		
		s->loadFromFiles(vertShaderFilePath, fragShaderFilePath);
		
		shaders[shader] = s;
	}
	
	bool ShaderManager::hasShader(std::string shader)
	{
		if(getShader(shader) != NULL)
			return true;
		return false;
	}
	
	IShader* ShaderManager::getShader(std::string shader)
	{
		IShader* s = shaders[shader];
		return s;
	}
	
	void ShaderManager::useShader(std::string shader)
	{
		IShader* s = getShader(shader);
		if(s != NULL)
		{
			s->enable();
			currentShader = s;
		}
	}
	
	IShader* ShaderManager::getCurrentShader()
	{
		return currentShader;
	}
}
