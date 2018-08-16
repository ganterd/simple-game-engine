#ifndef SGE_GLSL_SHADER_HPP
#define SGE_GLSL_SHADER_HPP

#include <GL/glew.h>
#include <GL/glu.h>

#include <easylogging++.h>

#include <sge/graphics/shaders/SubShader.hpp>
#include <sge/graphics/GLSLRenderTarget.hpp>

namespace SGE
{
	class Export GLSLShader : public SubShader
	{
	private:
		GLuint vShaderID;
		GLuint fShaderID;
		GLuint gShaderID;

		GLuint shaderID;

		const char* readShaderCode(std::string file);
		GLuint loadShader(const char* shaderCode, GLuint shaderType, GLuint targetProgram);

		std::map<std::string, GLuint> mUniformsMap;
		GLuint getUniformLocation(std::string name);

	public:
		GLSLShader();
		~GLSLShader();

		void setToRenderTarget(bool b);
		void getRenderTargetBuffer(std::string bufferName);

		bool addShaderFile(std::string shaderFile, ShaderType shaderType);
		bool loadFromFiles(std::string vFile, std::string fFile);
		bool loadFromFiles(std::string vFile, std::string fFile, std::string gFile);
		bool link();

		void enable();
		void disable();

		void setMVP(glm::mat4 mvpMat);

		virtual void setVariable(std::string name, bool value);
		virtual void setVariable(std::string name, int value);
		virtual void setVariable(std::string name, float value);
		virtual void setVariable(std::string name, glm::vec2 value);
		virtual void setVariable(std::string name, glm::vec3 value);
		virtual void setVariable(std::string name, glm::mat4 value);
	};
}

#endif
