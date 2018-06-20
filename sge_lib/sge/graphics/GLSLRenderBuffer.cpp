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
		this->m_width = width;
		this->m_height = height;
		this->m_bufferType = textureType;
		this->m_glRenderBufferType = this->_bufferTypeToGLInternalFormat(this->m_bufferType);
		this->m_dataType = dataType;
		this->m_glDataType = GLSLTexture::dataTypeToGLDataType(this->m_dataType);
		this->m_glFrameBufferID = glFBO;
		this->m_glTextureUnit = GL_TEXTURE0; // TODO: tmp
		this->m_glColorAttachment = glColorAttachment;


		LOG(INFO) << "Creating GLSLRenderBuffer (" << width << "x" << height << ")";

		glBindFramebuffer(GL_FRAMEBUFFER, glFBO);

		glGenRenderbuffers(1, &this->m_glRenderBufferID);

		glBindRenderbuffer(GL_RENDERBUFFER, this->m_glRenderBufferID);
		glRenderbufferStorage(
			GL_RENDERBUFFER,
			this->m_glRenderBufferType,
			this->m_width,
			this->m_height
		);
		glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,
			this->m_glColorAttachment,
			GL_RENDERBUFFER,
			this->m_glRenderBufferID
		);

		if(this->m_glColorAttachment != GL_DEPTH_ATTACHMENT)
		{
			glGenTextures(1, &this->m_glTextureID);
			glBindTexture(GL_TEXTURE_2D, this->m_glTextureID);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				this->m_glRenderBufferType,
				this->m_width,
				this->m_height,
				0,
				this->m_glRenderBufferType,
				this->m_glDataType,
				NULL
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


			glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				this->m_glColorAttachment,
				GL_TEXTURE_2D,
				this->m_glTextureID,
				0
			);
		}
		else
		{
			glGenTextures(1, &m_glTextureID);
			glBindTexture(GL_TEXTURE_2D, m_glTextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_glTextureID, 0);
		}
	}

	GLSLRenderBuffer::~GLSLRenderBuffer()
	{
		glDeleteTextures(1, &m_glTextureID);
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

	void GLSLRenderBuffer::bindTexture()
	{
		glActiveTexture(this->m_glTextureUnit);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->m_glTextureID);
	}

	void GLSLRenderBuffer::unbindTexture()
	{
		glActiveTexture(this->m_glTextureUnit);
		glBindTexture(GL_TEXTURE_2D, 0);
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
