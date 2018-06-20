#ifndef SGE_GLSL_RENDER_TARGET
#define SGE_GLSL_RENDER_TARGET

#include <GL/glew.h>
#include <GL/glu.h>

#include <vector>

#include <easylogging++.h>

#include <sge/graphics/IRenderTarget.hpp>
#include <sge/graphics/GLSLRenderBuffer.hpp>

namespace SGE
{
	class GLSLRenderTarget : public IRenderTarget
	{
	public:
		GLSLRenderTarget(int width, int height);
		~GLSLRenderTarget();

		virtual void bind();
		virtual void unbind();

		virtual void clear();

		unsigned int addRenderBuffer(IRenderBuffer::BufferType bufferType, ITexture::DataType dataType);

	private:

		GLuint fbo;
		GLuint rbo;

		GLenum* gBuffers;
		unsigned int gBufferCount;

		void initFBO();

		void updateBufferDimensions();
	};
}

#endif
