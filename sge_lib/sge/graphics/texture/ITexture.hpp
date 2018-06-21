#ifndef SGE_I_TEXTURE
#define SGE_I_TEXTURE

#include <string>
#include <iostream>

#include <sge/utils/stb_image.h>


#include <sge/utils/export.hpp>

namespace SGE
{
	class Export ITexture
	{
	friend class IRenderBuffer;
	friend class GLSLRenderBuffer;

	public:
		enum Type
		{
			Diffuse,
			Specular,
			Normals,
			Opacity,
			Other
		};

		enum Format
		{
			RGB,
			RGBA,
		};

		enum DataType
		{
			None,
			Byte,
			Float
		};

		virtual void bindTexture(int textureUnit) = 0;
		virtual void unbindTexture() = 0;

		Type type(){ return m_type; };

		virtual void loadFromFile(const std::string& path, Type type) = 0;

	protected:
		int m_width;
		int m_height;

		int mTextureID;
		int mTextureUnit;

		Type m_type;
		DataType m_dataType;

		const char* textureFilePath;
	};
}

#endif //SGE_I_TEXTURE
