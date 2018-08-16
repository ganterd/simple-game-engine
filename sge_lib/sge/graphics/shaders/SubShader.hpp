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
		bool mIsScreenSpaceShader;
		bool mToRenderTarget;
		IRenderTarget* mRenderTarget;


	public:
		enum ShaderType
		{
			Vertex,
			Geometry,
			Fragment
		};

		void setName(std::string n){ mName = n; };
		virtual void setToRenderTarget(bool b) = 0;
		virtual void getRenderTargetBuffer(std::string bufferName) = 0;

		virtual bool addShaderFile(std::string shaderFile, ShaderType shaderType) = 0;
		virtual bool loadFromFiles(std::string vertFile, std::string fragFile) = 0;
		virtual bool loadFromFiles(std::string vFile, std::string fFile, std::string gFile) = 0;

		virtual void enable() = 0;
		virtual void disable() = 0;

		const char* readFile(const char* filePath);

		virtual void setVariable(std::string name, bool value) = 0;
		virtual void setVariable(std::string name, int value) = 0;
		virtual void setVariable(std::string name, float value) = 0;
		virtual void setVariable(std::string name, glm::vec2 value) = 0;
		virtual void setVariable(std::string name, glm::vec3 value) = 0;
		virtual void setVariable(std::string name, glm::mat4 value) = 0;
	};
}

#endif
