#include <sge/graphics/shaders/SubShader.hpp>

namespace SGE
{
	void linkOutputToRenderBuffer(std::string shaderOutput, IRenderBuffer* buffer)
	{
		LOG(ERROR) << "No implementation to link output to render buffer";
	}

	void SubShader::linkOutputToRenderBuffer(
		std::string shaderOutput,
		IRenderBuffer* buffer
	){
		mRenderBufferOutputLinks[shaderOutput] = buffer;
	}

	void SubShader::linkInputFromRenderBuffer(IRenderBuffer* buffer, std::string targetSampler)
	{
		mRenderBufferInputLinks[targetSampler] = buffer;
	}
}
