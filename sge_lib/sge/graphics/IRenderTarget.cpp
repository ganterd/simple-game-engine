#include "IRenderTarget.hpp"

namespace SGE
{
	void IRenderTarget::setBufferDimensions(int w, int h)
	{
		mBufferWidth = w;
		mBufferHeight = h;
		updateBufferDimensions();
	}

	int IRenderTarget::getBufferWidth()
	{
		return mBufferWidth;
	}

	int IRenderTarget::getBufferHeight()
	{
		return mBufferHeight;
	}

	void IRenderTarget::setClearColour(float r, float g, float b, float a)
	{
		setClearColour(glm::vec4(r, g, b, a));
	}

	void IRenderTarget::setClearColour(glm::vec4 c)
	{
		mBufferClearColour = c;
	}

	unsigned int IRenderTarget::addRenderBuffer(IRenderBuffer* buffer)
	{
		mRenderBuffers.push_back(buffer);
		return (int)mRenderBuffers.size() - 1;
	}

	IRenderBuffer* IRenderTarget::getRenderBuffer(unsigned int idx)
	{
		if(idx >= mColourAttachments.size())
			return NULL;
		return mColourAttachments[idx];
	}

	IRenderBuffer* IRenderTarget::getRenderBuffer(std::string bufferName)
	{
		return mRenderBufferMap[bufferName];
	}

	void IRenderTarget::updateBufferDimensions()
	{
	}

	void IRenderTarget::updateBufferSelection()
	{
	}
}
