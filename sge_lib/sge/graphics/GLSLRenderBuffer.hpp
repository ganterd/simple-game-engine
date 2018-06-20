#ifndef SGE_GLSL_RENDER_BUFFER
#define SGE_GLSL_RENDER_BUFFER

#include <GL/glew.h>
#include <GL/glu.h>

#include <easylogging++.h>

#include <sge/graphics/IRenderBuffer.hpp>
#include <sge/graphics/texture/GLSLTexture.hpp>

namespace SGE
{
	class Export GLSLRenderBuffer : public IRenderBuffer
	{
		public:
			GLSLRenderBuffer(int width, int height, GLuint glFBO, IRenderBuffer::BufferType textureType, ITexture::DataType dataType, GLuint glColourAttachment);
			~GLSLRenderBuffer();

			void setGLTextureType(GLuint glTextureType);
			GLuint getGLTextureType();

			void setGLColorAttachment(GLuint glColorAttachment);
			GLuint getGLColorAttachment();

			void setGLDataType(GLuint glDataType);
			GLuint getGLDataType();

			void clear();

			virtual void bindBuffer();
			virtual void unbindBuffer();

			static bool checkFBOStatus();

		private:
			GLuint m_glRenderBufferID;
			GLuint m_glRenderBufferType;
			GLuint m_glDataType;
			GLuint m_glColorAttachment;
			GLuint m_glFrameBufferID;

			static GLuint _bufferTypeToGLInternalFormat(IRenderBuffer::BufferType type);
	};
}

#endif //SGE_GLSL_RENDER_BUFFER
