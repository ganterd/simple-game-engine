#ifndef SGE_I_TEXTURE
#define SGE_I_TEXTURE

#include <string>
#include <iostream>

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
			textureType_DIFFUSE,
			textureType_SPECULAR,
			textureType_SHININESS,
			textureType_AMBIENT,
			textureType_OPACITY,
			textureType_OTHER
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

		void LoadFromFile(const char* path);

		// TODO: Print size values
		friend std::ostream& operator<<(std::ostream& out, const ITexture& tex);

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
