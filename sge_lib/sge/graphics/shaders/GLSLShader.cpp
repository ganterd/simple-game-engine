#include <sge/graphics/shaders/GLSLShader.hpp>
#include <sge/graphics/shaders/ShaderManager.hpp>

namespace SGE
{
	GLSLShader::GLSLShader()
	{
		mRenderTarget = nullptr;
		mShaderProgramID = glCreateProgram();
	}

	GLSLShader::~GLSLShader()
	{
	}

	bool GLSLShader::addShaderFile(std::string shaderFile, ShaderType shaderType)
	{
		/* Convert internal shader type to GL enum */
		GLuint glShaderType = GL_VERTEX_SHADER;
		const char* sType = "unknown";
		switch(shaderType)
		{
			case Vertex:
				glShaderType = GL_VERTEX_SHADER;
				sType = "vertex";
				break;
			case Fragment:
				glShaderType = GL_FRAGMENT_SHADER;
				sType = "fragment";
				break;
			case Geometry:
				glShaderType = GL_GEOMETRY_SHADER;
				sType = "geometry";
				break;
		}
		LOG(DEBUG) << "Loading " << sType << " shader [" << shaderFile << "]";

		/* Read shader code from file*/
		const char* shaderCode = Utils::readFile(shaderFile);
		if(shaderCode == NULL)
		{
			LOG(ERROR) << "Could not read shader file '" << shaderFile << "'";
			return false;
		}

		/* Compile the shader and attach it to the current program */
		compileAndAttachShader(shaderCode, glShaderType);

		/* Free the shader code memory */
		delete[] shaderCode;

		/* Attempt to link the shader */
		return link();
	}

	bool GLSLShader::link()
	{
		/* Link the glsl shader program */
		glLinkProgram(mShaderProgramID);

		/* Check for errors */
		GLint linked = 0;
		glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			GLint logLength = 0;
			glGetProgramiv(mShaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
			GLchar* errorString = new GLchar[logLength];
			glGetProgramInfoLog(mShaderProgramID, logLength, &logLength, errorString);

			LOG(ERROR) << "Couldn't link shader: " << errorString;

			glDeleteShader(mShaderProgramID);
			delete[] errorString;
			return false;
		}
		else
		{
			return true;
		}
	}

	GLuint GLSLShader::compileAndAttachShader(
		const char* shaderCode,
		GLuint shaderType
	){
		if(shaderCode == NULL)
			return 0;

		/* Instantiate and compile new glsl shader */
		GLuint shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &shaderCode, 0);
		glCompileShader(shaderID);

		/* Make sure the shader compiled */
		GLint compiled;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			GLint logLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
			GLchar* errorString = new GLchar[logLength];
			glGetShaderInfoLog(shaderID, logLength, &logLength, errorString);

			const char* sType = shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment";
			LOG(ERROR) << "Couldn't compile " << sType << " shader:" << std::endl << errorString << std::endl;

			/* Delete the shader if it didn't */
			glDeleteShader(shaderID);
			delete[] errorString;
			return false;
		}
		else
		{
			/* Attach the shader to the parent shader program */
			glAttachShader(mShaderProgramID, shaderID);
			return shaderID;
		}
	}

	void GLSLShader::enable()
	{
		glUseProgram(mShaderProgramID);

		/* Attach outputs to render target, if any */
		if(mRenderTarget)
		{
			mRenderTarget->bind();
			mRenderTarget->clear();

			/* Attach outputs to frame buffers */
			std::map<std::string, IRenderBuffer*>::iterator it;
			it = mRenderBufferOutputLinks.begin();
			while(it != mRenderBufferOutputLinks.end())
			{
				GLuint attachment = glGetFragDataLocation(
					mShaderProgramID,
					it->first.c_str()
				);
				if(attachment != (GLuint)-1)
				{
					GLSLRenderBuffer* buffer = (GLSLRenderBuffer*)it->second;
					buffer->setGLColorAttachment(GL_COLOR_ATTACHMENT0 + attachment);
				}
				it++;
			}
		}

		/* Attach incoming render buffers to shader samplers */
		std::map<std::string, IRenderBuffer*>::iterator it;
		it = mRenderBufferInputLinks.begin();
		int textureUnit = 0;
		for(; it != mRenderBufferInputLinks.end(); it++)
		{
			GLSLRenderBuffer* linkedBuffer = (GLSLRenderBuffer*)it->second;
			setVariable(it->first, (int)textureUnit);
			linkedBuffer->bindTexture(textureUnit);
			textureUnit++;
		}
	}

	void GLSLShader::disable()
	{
		/* Unbind the render target */
		if(mRenderTarget)
			mRenderTarget->unbind();

		/* Unbind the textures */
		std::map<std::string, IRenderBuffer*>::iterator it = mRenderBufferInputLinks.begin();
		for(; it != mRenderBufferInputLinks.end(); it++)
		{
			IRenderBuffer* linkedBuffer = it->second;
			linkedBuffer->bindTexture(0);
		}

		/* Unbind the shader program */
		glUseProgram(0);
	}

	GLuint GLSLShader::getUniformLocation(std::string name)
	{
		std::map<std::string, GLuint>::iterator entry = mUniformsMap.find(name);
		if(entry != mUniformsMap.end())
		{
			return entry->second;
		}
		else
		{
			GLuint loc = glGetUniformLocation(mShaderProgramID, name.c_str());
			mUniformsMap[name] = loc;

			if(loc == (GLuint)-1)
				LOG(WARNING) << "Shader '" << mName
					<< "'[" << mShaderProgramID << "]"
					<< " has no uniform \"" << name << "\"";
			return loc;
		}
	}

	void GLSLShader::setVariable(std::string name, bool value)
	{
		glUniform1i(getUniformLocation(name), value ? 1 : 0);
	}

	void GLSLShader::setVariable(std::string name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void GLSLShader::setVariable(std::string name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void GLSLShader::setVariable(std::string name, glm::vec2 value)
	{
		glUniform2f(getUniformLocation(name), value.x, value.y);
	}

	void GLSLShader::setVariable(std::string name, glm::vec3 value)
	{
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
	}


	void GLSLShader::setVariable(std::string name, glm::mat4 value)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
	}

	GLuint GLSLShader::getSSBOBinding(const std::string& bufferName)
	{
		GLuint bufferResourceIndex = glGetProgramResourceIndex(
			mShaderProgramID,
			GL_SHADER_STORAGE_BLOCK,
			bufferName.c_str()
		);

		if (bufferResourceIndex == (GLuint)-1)
		{
			LOG_N_TIMES(1, WARNING) << "No SSBO '" << bufferName << "' in shader";
			return (GLuint)-1;
		}

		GLenum props[1] = { GL_BUFFER_BINDING };
		GLint returnedBinding[1];
		glGetProgramResourceiv(
			mShaderProgramID,
			GL_SHADER_STORAGE_BLOCK,
			bufferResourceIndex, 1,
			props, 1, NULL,
			returnedBinding
		);
		return (GLuint)returnedBinding[0];
	}


}
