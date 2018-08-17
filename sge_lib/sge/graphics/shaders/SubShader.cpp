#include <sge/graphics/shaders/SubShader.hpp>

namespace SGE
{
	const char* SubShader::readFile(const char* filePath)
	{
		char* text = nullptr;

		FILE *file = fopen(filePath, "r");

		if (file == NULL)
			return NULL;

		fseek(file, 0, SEEK_END);
		size_t count = ftell(file);
		rewind(file);


		if (count > 0) {
			text = (char*)malloc(sizeof(char) * (count + 1));
			count = fread(text, sizeof(char), count, file);
			text[count] = '\0';
		}
		fclose(file);

		return text;
	}

	void SubShader::addRenderBufferLink(
		std::string sourceShader,
		std::string sourceSubShader,
		std::string sourceBuffer,
		std::string targetSampler
	){
		RenderBufferLink link;
		link.sourceShader = sourceShader;
		link.sourceSubShader = sourceSubShader;
		link.sourceBuffer = sourceBuffer;
		link.targetSampler = targetSampler;
		mRenderBufferLinks.push_back(link);
	}
}
