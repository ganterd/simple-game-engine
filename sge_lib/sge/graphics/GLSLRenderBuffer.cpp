#include "GLSLRenderBuffer.hpp"

namespace SGE
{
	GLSLRenderBuffer::GLSLRenderBuffer(
			int width,
			int height,
			GLuint glFBO,
			IRenderBuffer::BufferType textureType,
			ITexture::DataType dataType,
			GLuint glColorAttachment
	)
	{
		mTexture = new GLSLTexture();
		mTexture->m_width = width;
		mTexture->m_height = height;
		mTexture->m_dataType = dataType;

		this->m_bufferType = textureType;
		this->m_glRenderBufferType = _bufferTypeToGLInternalFormat(this->m_bufferType);

		this->m_glDataType = GLSLTexture::dataTypeToGLDataType(mTexture->m_dataType);
		this->m_glFrameBufferID = glFBO;
		this->m_glColorAttachment = glColorAttachment;

		if(this->m_glColorAttachment != GL_DEPTH_ATTACHMENT)
		{
			glGenTextures(1, (GLuint*)&mTexture->mTextureID);
			glBindTexture(GL_TEXTURE_2D, mTexture->mTextureID);
			//glTexImage2D(GL_TEXTURE_2D,	0, m_glRenderBufferType, width, height, 0, this->m_glRenderBufferType, m_glDataType, NULL);
			glTexImage2D(GL_TEXTURE_2D,	0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture2D(GL_FRAMEBUFFER, m_glColorAttachment, GL_TEXTURE_2D, mTexture->mTextureID, 0);
		}
		else
		{
			glGenTextures(1, (GLuint*)&mTexture->mTextureID);
			glBindTexture(GL_TEXTURE_2D, mTexture->mTextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mTexture->mTextureID, 0);
		}



		LOG(INFO) << "Creating GLSLRenderBuffer (" << width << "x" << height << ")";


		// glGenRenderbuffers(1, &this->m_glRenderBufferID);
		//
		// glBindRenderbuffer(GL_RENDERBUFFER, this->m_glRenderBufferID);
		// glRenderbufferStorage(
		// 	GL_RENDERBUFFER,
		// 	this->m_glRenderBufferType,
		// 	this->m_width,
		// 	this->m_height
		// );
		// glFramebufferRenderbuffer(
		// 	GL_FRAMEBUFFER,
		// 	this->m_glColorAttachment,
		// 	GL_RENDERBUFFER,
		// 	this->m_glRenderBufferID
		// );


	}

	GLSLRenderBuffer::~GLSLRenderBuffer()
	{
		glDeleteTextures(1, (GLuint*)&mTexture->mTextureID);
		glDeleteRenderbuffers(1, &m_glRenderBufferID);
	}

	void GLSLRenderBuffer::setGLTextureType(GLuint glTextureType)
	{
		this->m_glRenderBufferType = glTextureType;
	}

	GLuint GLSLRenderBuffer::getGLTextureType()
	{
		return this->m_glRenderBufferType;
	}

	void GLSLRenderBuffer::setGLColorAttachment(GLuint glColorAttachment)
	{
		this->m_glColorAttachment = glColorAttachment;
	}

	GLuint GLSLRenderBuffer::getGLColorAttachment()
	{
		return this->m_glColorAttachment;
	}

	void GLSLRenderBuffer::setGLDataType(GLuint glDataType)
	{
		this->m_glDataType = glDataType;
	}

	GLuint GLSLRenderBuffer::getGLDataType()
	{
		return this->m_glDataType;
	}

	void GLSLRenderBuffer::bindBuffer()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, this->m_glRenderBufferID);
	}

	void GLSLRenderBuffer::unbindBuffer()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void GLSLRenderBuffer::clear()
	{
		// TODO: Implement clear buffer
	}

	GLuint GLSLRenderBuffer::_bufferTypeToGLInternalFormat(IRenderBuffer::BufferType type)
	{
		GLuint glRenderBufferType;
		switch(type)
		{
			case BufferType::Color:
				glRenderBufferType = GL_RGBA;
				break;
			case BufferType::Normal:
				glRenderBufferType = GL_RGBA16F;
				break;
			case BufferType::Position:
				glRenderBufferType = GL_RGBA32F;
				break;
			case BufferType::Depth:
				glRenderBufferType = GL_DEPTH_COMPONENT24;
				break;
			default:
				LOG(WARNING) << "Unrecognised buffer type requested";
				glRenderBufferType = GL_RGBA;
		}

		return glRenderBufferType;
	}

	bool GLSLRenderBuffer::checkFBOStatus()
	{
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch(status)
		{
		case GL_FRAMEBUFFER_COMPLETE:
			LOG(DEBUG) << "FBO is aaallll good!";
			return true;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			LOG(ERROR) << "FBO Error: Incomplete Attachment (GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			LOG(ERROR) << "FBO Error: Incomplete Missing Attachment (GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			LOG(ERROR) << "FBO Error: Incomplete Draw Buffer (GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			LOG(ERROR) << "FBO Error: Incomplete Read Buffer (GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			LOG(ERROR) << "FBO Error: Unsupported (GL_FRAMEBUFFER_UNSUPPORTED)";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			LOG(ERROR) << "FBO Error: Incomplete Multisample (GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			LOG(ERROR) << "FBO Error: Incomplete Layer Targets (GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)";
			break;
		default:
			LOG(ERROR) << "FBO Error: For some reason, GL decided not to give a known error code...";
		}
		return false;
	}
}
