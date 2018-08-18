#include <sge/graphics/shaders/GLSLShader.hpp>
#include <sge/graphics/shaders/ShaderManager.hpp>

namespace SGE
{
	GLSLShader::GLSLShader()
	{
		mRenderTarget = nullptr;
		mToRenderTarget = false;
		mFragmentShaderCount = 0;
		mBoundFragLocations = false;
		mIsScreenSpaceShader = false;
		shaderID = glCreateProgram();
	}

	GLSLShader::~GLSLShader()
	{
		//delete this->renderTarget;
	}

	bool GLSLShader::loadFromFiles(std::string vFile, std::string fFile)
	{
		return this->loadFromFiles(vFile, "", fFile);
	}

	bool GLSLShader::addShaderFile(std::string shaderFile, ShaderType shaderType)
	{
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

		const char* shaderCode = readShaderCode(shaderFile);

		if(shaderCode == NULL)
			return false;

		loadShader(shaderCode, glShaderType, shaderID);

		if(shaderType == Fragment)
		{
			mFragmentShaderCount++;
		}

		delete[] shaderCode;

		return link();
	}

	bool GLSLShader::loadFromFiles(
		std::string vertShaderFile,
		std::string geomShaderFile,
		std::string fragShaderFile
	){
		addShaderFile(vertShaderFile, ShaderType::Vertex);
		addShaderFile(geomShaderFile, ShaderType::Geometry);
		addShaderFile(fragShaderFile, ShaderType::Fragment);
		return true;
	}

	bool GLSLShader::link()
	{
		// Prior to linking, render buffers must be assigned
		if(mToRenderTarget && mRenderTarget && !mBoundFragLocations)
		{
			mRenderTarget->bind();
			std::vector<IRenderBuffer*> renderBuffers = mRenderTarget->getColourAttachmentBuffers();
			for(IRenderBuffer* renderBuffer : renderBuffers)
			{
				flushGLErrors();
				GLSLRenderBuffer* buffer = (GLSLRenderBuffer*)renderBuffer;
				buffer->bindBuffer();
				glBindFragDataLocation(shaderID, buffer->getGLColorAttachment() - GL_COLOR_ATTACHMENT0, buffer->mName.c_str());
				LOG(DEBUG) << "Binding attachment " << buffer->getGLColorAttachment() - GL_COLOR_ATTACHMENT0 << " variable " << buffer->mName;

				checkGLErrors();
			}
			mBoundFragLocations = true;
		}


		glLinkProgram(shaderID);

		if(mRenderTarget && mFragmentShaderCount)
		{
			for(IRenderBuffer* renderBuffer : mRenderTarget->getColourAttachmentBuffers())
			{
				GLSLRenderBuffer* buffer = (GLSLRenderBuffer*)renderBuffer;
				GLuint want = glGetFragDataLocation(shaderID, buffer->mName.c_str());
				LOG(DEBUG) << "Bound '" << buffer->mName << "' to attachment " << want;
				checkGLErrors();
			}
		}

		GLint linked = 0;
		glGetProgramiv(shaderID, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE)
		{
			GLint logLength = 0;
			glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
			GLchar* errorString = new GLchar[logLength];
			glGetProgramInfoLog(shaderID, logLength, &logLength, errorString);

			LOG(ERROR) << "Couldn't link shader: " << errorString << std::endl;

			glDeleteShader(shaderID);
			delete[] errorString;
			return false;
		}
		return true;
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
			GLuint loc = glGetUniformLocation(shaderID, name.c_str());
			mUniformsMap[name] = loc;

			if(loc == (GLuint)-1)
				LOG(WARNING) << "Shader '" << mName << "'[" << shaderID << "] has no uniform \"" << name << "\"";
			return loc;
		}
	}

	void GLSLShader::setToRenderTarget(bool b)
	{
		mToRenderTarget = b;
		if(mToRenderTarget)
		{
			mRenderTarget = new GLSLRenderTarget();
		}
	}

	void GLSLShader::getRenderTargetBuffer(std::string bufferName)
	{

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

	const char* GLSLShader::readShaderCode(std::string file)
	{
		if(file.empty())
		{
			return NULL;
		}

		const char* shaderCode = readFile(file.c_str());
		if(!shaderCode){
			LOG(WARNING) << "Could not read shader file: " << file;
			return NULL;
		}

		return shaderCode;
	}

	GLuint GLSLShader::loadShader(const char* shaderCode, GLuint shaderType, GLuint targetProgram)
	{
		if(shaderCode == NULL)
			return 0;

		// TODO: Add some error sutff in here
		GLuint shaderID = glCreateShader(shaderType);

		glShaderSource(shaderID, 1, &shaderCode, 0);
		glCompileShader(shaderID);

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
			glDeleteShader(shaderID);
			delete[] errorString;
			return false;
		}


		glAttachShader(targetProgram, shaderID);
		return shaderID;
	}

	void GLSLShader::enable()
	{
		glUseProgram(shaderID);

		if(mToRenderTarget && mRenderTarget)
		{
			mRenderTarget->bind();
			mRenderTarget->clear();
		}

		for(RenderBufferLink l : mRenderBufferLinks)
		{
			Shader* linkedShader = ShaderManager::getShader(l.sourceShader);
			SubShader* linkedSubShader = linkedShader->getSubShader(l.sourceSubShader);
			IRenderTarget* linkedRenderTarget = linkedSubShader->getRenderTarget();

			if(!linkedRenderTarget)
			{
				LOG(WARNING) << "Linked render buffer '" << l.sourceShader << "." << l.sourceSubShader << "' is not a render target";
				continue;
			}

			GLSLRenderBuffer* linkedBuffer = (GLSLRenderBuffer*)linkedRenderTarget->getRenderBuffer(l.sourceBuffer);
			GLuint textureUnit = linkedBuffer->getGLColorAttachment() - GL_COLOR_ATTACHMENT0;

			setVariable(l.targetSampler, (int)textureUnit);
			linkedBuffer->bindTexture(textureUnit);
		}
	}

	void GLSLShader::disable()
	{
		if(mToRenderTarget && mRenderTarget)
		{
			mRenderTarget->unbind();
		}
		glUseProgram(0);
	}
}
