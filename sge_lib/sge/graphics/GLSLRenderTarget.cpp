#include "GLSLRenderTarget.hpp"

namespace SGE
{
	GLSLRenderTarget::GLSLRenderTarget()
	{
		int bufferWidth = DisplayManager::getDisplayInstance()->size().width;
		int bufferHeight = DisplayManager::getDisplayInstance()->size().height;
		fbo = 0;
		mBufferWidth = bufferWidth;
		mBufferHeight = bufferHeight;
		gBuffers = NULL;
		gBufferCount = 0;

		initFBO();
		unbind();
	}

	GLSLRenderTarget::GLSLRenderTarget(int width, int height)
	{
		fbo = 0;
		mBufferWidth = width;
		mBufferHeight = height;
		gBuffers = NULL;
		gBufferCount = 0;

		initFBO();
		unbind();
		//addRenderBuffer(IRenderBuffer::BufferType::Color, ITexture::DataType::Float);
		//addRenderBuffer(IRenderBuffer::BufferType::Depth, ITexture::DataType::Float);
	}

	GLSLRenderTarget::~GLSLRenderTarget()
	{
	}

	void GLSLRenderTarget::clear()
	{
		bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void GLSLRenderTarget::updateBufferDimensions()
	{
	}

	void GLSLRenderTarget::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		checkGLErrors();

		if(mColourAttachments.size() == 0)
		{
			LOG(ERROR) << "No colour attachments to bind to...";
		}
	}

	void GLSLRenderTarget::unbind()
	{
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
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		GLuint attachment;
		if(bufferType == IRenderBuffer::BufferType::Depth)
		{
			attachment = GL_DEPTH_ATTACHMENT;
		}
		else
		{
			attachment = GL_COLOR_ATTACHMENT0 + (GLuint)mColourAttachments.size();
		}

		GLSLRenderBuffer* buffer = new GLSLRenderBuffer(
			mBufferWidth,
			mBufferHeight,
			fbo,
			bufferType,
			dataType,
			attachment
		);
		mRenderBuffers.push_back(buffer);

		if(bufferType != IRenderBuffer::BufferType::Depth)
		{
			LOG(DEBUG) << "New colour attachment [" << attachment << "]";
			mColourAttachments.push_back(buffer);
			unsigned int* attachments = new unsigned int[mColourAttachments.size()];
			for(unsigned int i = 0; i < mColourAttachments.size(); ++i)
			{
				attachments[i] = ((GLSLRenderBuffer*)mColourAttachments[i])->getGLColorAttachment();
			}
			glDrawBuffers((int)mColourAttachments.size(), attachments);
			delete[] attachments;
		}

		GLSLRenderBuffer::checkFBOStatus();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		checkGLErrors();

		return (int)mRenderBuffers.size() - 1;
	}

	unsigned int GLSLRenderTarget::addRenderBuffer(
			std::string bufferName,
			IRenderBuffer::BufferType bufferType,
			ITexture::DataType dataType
	)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		GLuint attachment;
		if(bufferType == IRenderBuffer::BufferType::Depth)
		{
			attachment = GL_DEPTH_ATTACHMENT;
		}
		else
		{
			attachment = GL_COLOR_ATTACHMENT0 + (GLuint)mColourAttachments.size();
		}

		GLSLRenderBuffer* buffer = new GLSLRenderBuffer(
			mBufferWidth,
			mBufferHeight,
			fbo,
			bufferType,
			dataType,
			attachment
		);
		mRenderBuffers.push_back(buffer);
		mRenderBufferMap[bufferName] = buffer;
		buffer->mName = bufferName;

		if(bufferType != IRenderBuffer::BufferType::Depth)
		{
			LOG(DEBUG) << "New colour attachment [" << attachment << "]";
			mColourAttachments.push_back(buffer);
			unsigned int* attachments = new unsigned int[mColourAttachments.size()];
			for(unsigned int i = 0; i < mColourAttachments.size(); ++i)
			{
				attachments[i] = ((GLSLRenderBuffer*)mColourAttachments[i])->getGLColorAttachment();
			}
			glDrawBuffers((int)mColourAttachments.size(), attachments);
			delete[] attachments;
		}

		GLSLRenderBuffer::checkFBOStatus();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return (int)mRenderBuffers.size() - 1;
	}
}
