#include "GLSLRenderTarget.hpp"

namespace SGE
{
	GLSLRenderTarget::GLSLRenderTarget() : GLSLRenderTarget(0)
	{
	}

	GLSLRenderTarget::GLSLRenderTarget(unsigned short buffers)
	{
		fbo = 0;
		this->gBuffers = NULL;
		this->gBufferCount = 0;

		this->initFBO();
	}

	GLSLRenderTarget::~GLSLRenderTarget()
	{
	}

	void GLSLRenderTarget::clear()
	{
		this->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void GLSLRenderTarget::updateBufferDimensions()
	{
		// TODO: Update target dimensions
	}

	void GLSLRenderTarget::bind()
	{
		if(this->m_renderBuffers.size() > 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);

			// TODO: Update so
			// glDrawBuffers(this->m_renderBuffers.size(), [colour attachments]);
			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			GLenum buffers[] = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, buffers);
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	void GLSLRenderTarget::unbind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GLSLRenderTarget::initFBO()
	{
		glGenFramebuffers(1, &fbo);

		GLSLRenderBuffer::checkFBOStatus();
	}

	unsigned int GLSLRenderTarget::addRenderBuffer(
			IRenderBuffer::BufferType bufferType,
			ITexture::DataType dataType
	)
	{
		GLuint colorAttachment = GL_COLOR_ATTACHMENT0 + this->m_renderBuffers.size();
		if(bufferType == IRenderBuffer::BufferType::Depth)
			colorAttachment = GL_DEPTH_ATTACHMENT;

		glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
		IRenderBuffer* buffer = new GLSLRenderBuffer(
			this->bufferWidth,
			this->bufferHeight,
			this->fbo,
			bufferType,
			dataType,
			colorAttachment
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		this->m_renderBuffers.push_back(buffer);

		return this->m_renderBuffers.size() - 1;
	}
}
