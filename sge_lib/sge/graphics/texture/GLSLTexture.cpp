#include "GLSLTexture.hpp"

namespace SGE
{
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
}
