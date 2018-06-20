#ifndef SGE_I_RENDER_TARGET
#define SGE_I_RENDER_TARGET

#include <vector>

#include <easylogging++.h>
#include <glm/glm.hpp>

#include <sge/graphics/IRenderBuffer.hpp>
#include <sge/graphics/texture/ITexture.hpp>

namespace SGE
{
	class Export IRenderTarget
	{
	public:
		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void clear() = 0;
		void setClearColour(float r, float g, float b, float a);
		void setClearColour(glm::vec4 c);

		void setBufferDimensions(int w, int h);
		int getBufferWidth();
		int getBufferHeight();

		virtual unsigned int addRenderBuffer(IRenderBuffer::BufferType bufferType, ITexture::DataType dataType) = 0;
		unsigned int addRenderBuffer(IRenderBuffer* buffer);
		unsigned int addRenderBuffer(IRenderBuffer* buffer, unsigned int idx);
		IRenderBuffer* getRenderBuffer(unsigned int bufferIndex);
		void removeRenderBuffer(unsigned int bufferIndex);
		void removeRenderBuffer(IRenderBuffer* buffer);

	protected:
		int bufferWidth;
		int bufferHeight;

		glm::vec4 bufferClearColour;

		std::vector<IRenderBuffer*> m_renderBuffers;

		/* Called after the dimensions are set. */
		virtual void updateBufferDimensions();

		/* Called after a buffer is set or unset. Not mandatory */
		virtual void updateBufferSelection();

	private:
	};
}

#endif // SGE_I_RENDER_TARGET
