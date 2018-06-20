#include "IShader.hpp"

namespace SGE
{
	void IShader::setTargetBufferDimensions(int w, int h)
	{
		LOG(DEBUG) << "Updating shader dimensions to " << w << "x" << h;
		this->targetBufferWidth = w;
		this->targetBufferHeight =h;
		this->updateTargetBufferDimensions();
		//this->renderTarget->setBufferDimensions(w, h);
	}

	const char* IShader::readFile(const char* filePath)
	{
		char* text;

		FILE *file = fopen(filePath, "r");

		if (file == NULL)
			return NULL;

		fseek(file, 0, SEEK_END);
		int count = ftell(file);
		rewind(file);


		if (count > 0) {
			text = (char*)malloc(sizeof(char) * (count + 1));
			count = fread(text, sizeof(char), count, file);
			text[count] = '\0';
		}
		fclose(file);

		return text;
	}

	void IShader::setRenderTarget(IRenderTarget* rt)
	{
		if(this->renderTarget != NULL)
			delete this->renderTarget;

		this->renderTarget = rt;
	}

	IRenderTarget* IShader::getRenderTarget()
	{
		return this->renderTarget;
	}
}
