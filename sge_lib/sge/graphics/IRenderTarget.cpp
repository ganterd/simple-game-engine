#include "IRenderTarget.hpp"

namespace SGE
{
	void IRenderTarget::setBufferDimensions(int w, int h)
	{
		this->bufferWidth = w;
		this->bufferHeight = h;
		this->updateBufferDimensions();
	}
	
	int IRenderTarget::getBufferWidth()
	{
		return this->bufferWidth;
	}
	
	int IRenderTarget::getBufferHeight()
	{
		return this->bufferHeight;
	}
	
	void IRenderTarget::setClearColour(float r, float g, float b, float a)
	{
		this->setClearColour(glm::vec4(r, g, b, a));
	}
	
	void IRenderTarget::setClearColour(glm::vec4 c)
	{
		this->bufferClearColour = c;
	}
	
	unsigned int IRenderTarget::addRenderBuffer(IRenderBuffer* buffer)
	{
		this->m_renderBuffers.push_back(buffer);
		return this->m_renderBuffers.size() - 1;
	}
	
	IRenderBuffer* IRenderTarget::getRenderBuffer(unsigned int idx)
	{	
		if(idx >= this->m_renderBuffers.size())
			return NULL;
		return this->m_renderBuffers[idx];
	}
	
	void IRenderTarget::updateBufferDimensions()
	{
	}
	
	void IRenderTarget::updateBufferSelection()
	{
	}
}
