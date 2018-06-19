#ifndef SGE_GLSL_TEXTURE
#define SGE_GLSL_TEXTURE

#include <GL/glew.h>
#include <GL/glu.h>

#include <sge/graphics/texture/ITexture.hpp>

namespace SGE
{
	class GLSLTexture : public ITexture
	{
	public:
		GLSLTexture();
		~GLSLTexture();

		void bindTexture();
		void unbindTexture();

		static GLuint dataTypeToGLDataType(ITexture::DataType dataType);

	protected:
		GLuint m_glTexID;
	};
}

#endif
