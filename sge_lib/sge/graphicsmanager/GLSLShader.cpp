#include "GLSLShader.hpp"

namespace SGE
{
	GLSLShader::GLSLShader()
	{
	}
	
	bool GLSLShader::loadFromFiles(std::string vertFile, std::string fragFile)
	{
		LOG(INFO) << "Loading shaders";
		LOG(INFO) << " |- Vert: " << vertFile;
		LOG(INFO) << " |- Frag: " << fragFile;
		
		const char* vertShaderCode = readFile(vertFile.c_str());
		if(!vertShaderCode){
			LOG(WARNING) << "Could not read vert shader file";
			return false;
		}
		
		const char* fragShaderCode = readFile(fragFile.c_str());
		if(!fragShaderCode){
			LOG(WARNING) << "Could not read frag shader file";
			return false;
		}

		this->vShaderID = glCreateShader(GL_VERTEX_SHADER);
		this->fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(this->vShaderID, 1, &vertShaderCode, 0);
		glShaderSource(this->fShaderID, 1, &fragShaderCode, 0);

		glCompileShader(this->vShaderID);
		glCompileShader(this->fShaderID);

		this->shaderID = glCreateProgram();

		glAttachShader(this->shaderID, this->vShaderID);
		glAttachShader(this->shaderID, this->fShaderID);
		glLinkProgram(this->shaderID);
		
		this->locMVP = glGetUniformLocation(this->shaderID, SGE_MVP_SHADER_MAT);
		if(this->locMVP == -1)
		{
			LOG(WARNING) << "Couldn't find shader variable '" << SGE_MVP_SHADER_MAT << "'";
		}
	}
	
	void GLSLShader::enable()
	{
		glUseProgram(this->shaderID);
	}
	
	void GLSLShader::disable()
	{
		glUseProgram(0);
	}
	
	void GLSLShader::setMVP(glm::mat4 mvpMat)
	{
		//std::cout << this->locMVP;
		glUniformMatrix4fv(this->locMVP, 1, GL_FALSE, &mvpMat[0][0]);
	}
}
