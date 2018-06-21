#include "GLSLTexture.hpp"

namespace SGE
{
	GLSLTexture::GLSLTexture()
	{
		mTextureID = -1;
		m_type = ITexture::Type::Other;
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

	void GLSLTexture::loadFromFile(const std::string& path, Type type)
	{
		int width = 0;
		int height = 0;
		int channels = 0;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if(width == 0 || height == 0 || channels == 0)
		{
			LOG(ERROR) << "Couldn't load texture: " << path;
			return;
		}
		LOG(INFO) << "Texture " << path << " loaded [" << width << "x" << height << "x" << channels << "]";

		GLuint glType;
		switch(channels)
		{
		case 1:
			glType = GL_R;
			break;
		case 2:
			glType = GL_RG;
			break;
		case 3:
			glType = GL_RGB;
			break;
		case 4:
			glType = GL_RGBA;
			break;
		default:
			LOG(ERROR) << "Too many channels!!";
			return;
		}

		glGenTextures(1, (GLuint*)&mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		//glTexImage2D(GL_TEXTURE_2D,	0, m_glRenderBufferType, width, height, 0, this->m_glRenderBufferType, m_glDataType, NULL);
		glTexImage2D(GL_TEXTURE_2D,	0, GL_RGBA, width, height, 0, glType, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);

		m_type = type;
	}
}
