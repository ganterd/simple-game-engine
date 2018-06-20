#include "IRenderBuffer.hpp"

namespace SGE
{
	IRenderBuffer::BufferType IRenderBuffer::getBufferType()
	{
		return this->m_bufferType;
	}

	void IRenderBuffer::bindTexture(int textureUnit)
	{
		mTexture->bindTexture(textureUnit);
	}

	void IRenderBuffer::unbindTexture()
	{
		mTexture->unbindTexture();
	}
}
