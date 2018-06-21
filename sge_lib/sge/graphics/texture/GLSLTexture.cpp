#include "GLSLTexture.hpp"

namespace SGE
{
	GLSLTexture::GLSLTexture()
	{
		mTextureID = -1;
	}

	GLSLTexture::~GLSLTexture()
	{

	}

	GLuint GLSLTexture::dataTypeToGLDataType(ITexture::DataType dataType)
	{
		GLuint glType;

		switch(dataType)
		{
			case DataType::Byte:
				glType = GL_UNSIGNED_BYTE;
				break;
			case DataType::Float:
				glType = GL_FLOAT;
				break;
			default:
				glType = GL_UNSIGNED_BYTE;
		}

		return glType;
	}

	void GLSLTexture::bindTexture(int textureUnit)
	{
		mTextureUnit = textureUnit;
		glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
	}

	void GLSLTexture::unbindTexture()
	{
        glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
