#include "ITexture.hpp"

namespace SGE
{
	void ITexture::LoadFromFile(const char* textureFilePath)
	{
		this->textureFilePath = textureFilePath;
	}
	
	std::ostream& operator<<(std::ostream& out, const ITexture& tex)
	{
		std::string t;
		if(tex.m_type == ITexture::Type::textureType_DIFFUSE)
			t = "Texture (Diffuse)";
		else if(tex.m_type == ITexture::Type::textureType_OPACITY)
			t = "Texture (Opacity)";
		else
			t = "Texture (Other)";
		
		out << t;
	}
}
