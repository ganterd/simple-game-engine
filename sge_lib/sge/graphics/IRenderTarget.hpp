#ifndef SGE_I_RENDER_TARGET
#define SGE_I_RENDER_TARGET

#include <vector>

#include <easylogging++.h>
#include <glm/glm.hpp>

#include <sge/graphics/IRenderBuffer.hpp>
#include <sge/graphics/texture/ITexture.hpp>

namespace SGE
{
	class IRenderTarget
	{
	public:
		Export virtual void bind() = 0;
		Export virtual void unbind() = 0;

		Export virtual void clear() = 0;
		Export void setClearColour(float r, float g, float b, float a);
		Export void setClearColour(glm::vec4 c);

		Export void setBufferDimensions(int w, int h);
		Export int getBufferWidth();
		Export int getBufferHeight();

		Export virtual unsigned int addRenderBuffer(IRenderBuffer::BufferType bufferType, ITexture::DataType dataType) = 0;
		Export unsigned int addRenderBuffer(IRenderBuffer* buffer);
		Export unsigned int addRenderBuffer(IRenderBuffer* buffer, unsigned int idx);
		Export IRenderBuffer* getRenderBuffer(unsigned int bufferIndex);
		Export void removeRenderBuffer(unsigned int bufferIndex);
		Export void removeRenderBuffer(IRenderBuffer* buffer);

	protected:
		int mBufferWidth;
		int mBufferHeight;
		glm::vec4 mBufferClearColour;

		std::vector<IRenderBuffer*> mRenderBuffers;
		std::vector<IRenderBuffer*> mColourAttachments;

		/* Called after the dimensions are set. */
		virtual void updateBufferDimensions();

		/* Called after a buffer is set or unset. Not mandatory */
		virtual void updateBufferSelection();

	private:
	};
}

#endif // SGE_I_RENDER_TARGET
