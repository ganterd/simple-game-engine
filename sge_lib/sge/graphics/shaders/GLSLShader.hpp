#ifndef SGE_GLSL_SHADER_HPP
#define SGE_GLSL_SHADER_HPP

#include <GL/glew.h>
#include <GL/glu.h>

#include <easylogging++.h>

#include <sge/graphics/shaders/SubShader.hpp>
#include <sge/graphics/GLSLRenderTarget.hpp>
#include <sge/graphics/OGLGraphicsManager.hpp>

namespace SGE
{
	class Export GLSLShader : public SubShader
	{
	private:
		GLuint mShaderProgramID;
		GLuint compileAndAttachShader(const char*, GLuint);
		bool link();

		std::map<std::string, GLuint> mUniformsMap;
		GLuint getUniformLocation(std::string name);

	public:
		GLSLShader();
		~GLSLShader();

		bool addShaderFile(std::string shaderFile, ShaderType shaderType);


		GLuint getSSBOBinding(const std::string& bufferName);

		void enable();
		void disable();
		void setVariable(std::string name, bool value);
		void setVariable(std::string name, int value);
		void setVariable(std::string name, float value);
		void setVariable(std::string name, glm::vec2 value);
		void setVariable(std::string name, glm::vec3 value);
		void setVariable(std::string name, glm::vec4 value);
		void setVariable(std::string name, glm::mat4 value);
	};
}

#endif
