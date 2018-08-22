#include "ShaderManager.hpp"

namespace SGE
{
	Shader* ShaderManager::currentShader = NULL;
	std::map<std::string, Shader*> ShaderManager::shaders;

	void ShaderManager::init()
	{
		currentShader = NULL;
	}

	void ShaderManager::addShader(std::string shaderName, Shader* shader)
	{
		if(hasShader(shaderName))
			LOG(WARNING) << "Overwriting shader '" << shaderName << "'";
		shaders[shaderName] = shader;
	}

	bool ShaderManager::hasShader(std::string shader)
	{
		if(shaders.count(shader) > 0)
			return true;
		return false;
	}

	Shader* ShaderManager::getShader(std::string shader)
	{
		Shader* s = NULL;
		if(hasShader(shader))
		{
			s = shaders[shader];
		}

		return s;
	}

	void ShaderManager::setCurrentShader(Shader* s)
	{
		if(currentShader != nullptr)
			currentShader->disable();
		currentShader = s;
		if(currentShader != nullptr)
			currentShader->enable();
	}

	Shader* ShaderManager::useShader(std::string shader)
	{
		Shader* s = getShader(shader);
		if(s != nullptr)
		{
			setCurrentShader(s);
			return currentShader;
		}
		else
		{
			LOG(WARNING) << "No shader with name '" << shader << "'";
			return nullptr;
		}
	}

	Shader* ShaderManager::getCurrentShader()
	{
		return currentShader;
	}
}
