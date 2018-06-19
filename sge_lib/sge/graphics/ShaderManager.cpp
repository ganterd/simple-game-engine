#include "ShaderManager.hpp"

namespace SGE
{
	IShader* ShaderManager::currentShader = NULL;
	std::string ShaderManager::shaderFolder = "../../shaders/";
	std::map<std::string, IShader*> ShaderManager::shaders;

	int ShaderManager::targetBufferWidth = 1;
	int ShaderManager::targetBufferHeight = 1;

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

		std::string geomShaderFilePath = shaderFolder;
		geomShaderFilePath.append(shader);
		geomShaderFilePath.append(".geom");

		s->loadFromFiles(vertShaderFilePath, geomShaderFilePath, fragShaderFilePath);
		s->setTargetBufferDimensions(
			ShaderManager::targetBufferWidth,
			ShaderManager::targetBufferHeight
		);

		shaders[shader] = s;
	}

	bool ShaderManager::hasShader(std::string shader)
	{
		if(shaders.count(shader) > 0)
			return true;
		return false;
	}

	IShader* ShaderManager::getShader(std::string shader)
	{
		IShader* s = NULL;
		if(hasShader(shader))
		{
			s = shaders[shader];
		}

		return s;
	}

	void ShaderManager::useShader(std::string shader)
	{
		if(currentShader != NULL)
			currentShader->disable();

		IShader* s = getShader(shader);
		if(s != NULL)
		{
			s->enable();
			//s->setTargetBufferDimensions(targetBufferWidth, targetBufferHeight);
			currentShader = s;
		}
		else
		{
			LOG(WARNING) << "No shader with name '" << shader << "'";
		}
	}

	IShader* ShaderManager::getCurrentShader()
	{
		return currentShader;
	}

	void ShaderManager::setTargetBufferDimensions(int w, int h)
	{
		targetBufferWidth = w;
		targetBufferHeight = h;

		if(currentShader != NULL)
		{
			currentShader->setTargetBufferDimensions(targetBufferWidth, targetBufferHeight);
		}
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
