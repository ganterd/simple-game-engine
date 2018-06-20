#ifndef SGE_I_RENDER_BUFFER
#define SGE_I_RENDER_BUFFER

#include <sge/graphics/texture/ITexture.hpp>

namespace SGE
{
	class Export IRenderBuffer
	{
	public:
		enum BufferType
		{
			Color,
			Normal,
			Position,
			Depth
		};

		virtual void bindBuffer() = 0;
		virtual void unbindBuffer() = 0;
		virtual void bindTexture(int textureUnit = 0);
		virtual void unbindTexture();

		virtual void clear() = 0;

		BufferType getBufferType();

	protected:
		BufferType m_bufferType;
		ITexture* mTexture;
	};
}

#endif
