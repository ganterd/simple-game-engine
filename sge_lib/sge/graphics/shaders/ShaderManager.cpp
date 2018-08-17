#include "ShaderManager.hpp"

namespace SGE
{
	Shader* ShaderManager::currentShader = NULL;
	std::map<std::string, Shader*> ShaderManager::shaders;

	int ShaderManager::targetBufferWidth = 1;
	int ShaderManager::targetBufferHeight = 1;

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
	}

	Shader* ShaderManager::useShader(std::string shader)
	{
		Shader* s = getShader(shader);
		if(s != nullptr)
		{
			setCurrentShader(s);
			s->useSubShader(0);
			return currentShader;
		}
		else
		{
			LOG(WARNING) << "No shader with name '" << shader << "'";
			return nullptr;
		}
	}

	SubShader* ShaderManager::useShader(std::string shaderName, std::string subShaderName)
	{
		Shader* s = getShader(shaderName);
		if(s != nullptr)
		{
			SubShader* subShader = s->useSubShader(subShaderName);
			//s->setTargetBufferDimensions(targetBufferWidth, targetBufferHeight);
			if(subShader)
			{
				setCurrentShader(s);
				return subShader;
			}
			else
			{
				LOG(WARNING) << "Shader '" << shaderName << "' has no sub shader '" << subShader << "'";
				return nullptr;
			}
		}
		else
		{
			LOG(WARNING) << "No shader with name '" << shaderName << "'";
			return nullptr;
		}
	}

	Shader* ShaderManager::getCurrentShader()
	{
		return currentShader;
	}

	SubShader* ShaderManager::getCurrentSubShader()
	{
		if(currentShader)
			return currentShader->getCurrentSubShader();
		return nullptr;
	}

	void ShaderManager::setTargetBufferDimensions(int w, int h)
	{
		targetBufferWidth = w;
		targetBufferHeight = h;
	}

	int ShaderManager::getTargetBufferWidth()
	{
		return targetBufferWidth;
	}

	int ShaderManager::getTargetBufferHeight()
	{
		return targetBufferHeight;
	}
}
