#ifndef SGE_I_RENDER_BUFFER
#define SGE_I_RENDER_BUFFER

#include <sge/graphics/texture/ITexture.hpp>

namespace SGE
{
	class IRenderBuffer : public ITexture
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

		virtual void clear() = 0;

		BufferType getBufferType();

	protected:
		BufferType m_bufferType;
	};
}

#endif
