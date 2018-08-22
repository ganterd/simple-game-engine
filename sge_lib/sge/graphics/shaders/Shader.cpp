#include <sge/graphics/shaders/Shader.hpp>

namespace SGE
{
	void linkOutputToRenderBuffer(std::string shaderOutput, IRenderBuffer* buffer)
	{
		LOG(ERROR) << "No implementation to link output to render buffer";
	}

	void Shader::linkOutputToRenderBuffer(
		std::string shaderOutput,
		IRenderBuffer* buffer
	){
		mRenderBufferOutputLinks[shaderOutput] = buffer;
	}

	void Shader::linkInputFromRenderBuffer(IRenderBuffer* buffer, std::string targetSampler)
	{
		mRenderBufferInputLinks[targetSampler] = buffer;
	}
}
