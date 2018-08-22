#ifndef SGE_ISHADER_HPP
#define SGE_ISHADER_HPP

#ifndef SGE_MVP_SHADER_MAT
#define SGE_MVP_SHADER_MAT "modelViewProjection"
#endif

#define SGE_SHADER_BUFFER_WIDTH "bufferWidth"
#define SGE_SHADER_BUFFER_HEIGHT "bufferHeight"

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <glm/glm.hpp>

#include <sge/graphics/IRenderTarget.hpp>

namespace SGE
{
	class Export SubShader
	{
	protected:
		std::string mName;
		IRenderTarget* mRenderTarget;

		std::map<std::string, IRenderBuffer*> mRenderBufferOutputLinks;
		std::map<std::string, IRenderBuffer*> mRenderBufferInputLinks;

	public:
		enum ShaderType
		{
			Vertex,
			Geometry,
			Fragment
		};

		void setName(std::string n){ mName = n; };
		virtual bool addShaderFile(std::string shaderFile, ShaderType shaderType) = 0;

		virtual void renderTarget(IRenderTarget* t){ mRenderTarget = t; };
		virtual IRenderTarget* renderTarget(){ return mRenderTarget; };

		virtual void linkOutputToRenderBuffer(std::string shaderOutput, IRenderBuffer* buffer);
		virtual void linkInputFromRenderBuffer(IRenderBuffer* buffer, std::string targetSampler);

		virtual void enable() = 0;
		virtual void disable() = 0;
		virtual void setVariable(std::string name, bool value) = 0;
		virtual void setVariable(std::string name, int value) = 0;
		virtual void setVariable(std::string name, float value) = 0;
		virtual void setVariable(std::string name, glm::vec2 value) = 0;
		virtual void setVariable(std::string name, glm::vec3 value) = 0;
		virtual void setVariable(std::string name, glm::vec4 value) = 0;
		virtual void setVariable(std::string name, glm::mat4 value) = 0;
	};
}

#endif
