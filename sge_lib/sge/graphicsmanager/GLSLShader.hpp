#ifndef SGE_GLSL_SHADER_HPP
#define SGE_GLSL_SHADER_HPP

#include <GL/glew.h>
#include <GL/glu.h>

#include <easylogging++.h>

#include <sge/graphicsmanager/IShader.hpp>

namespace SGE
{
	class GLSLShader: public IShader
	{
	private:
		GLuint vShaderID;
		GLuint fShaderID;
		GLuint shaderID;
		
		GLuint locMVP;
		
	public:
		GLSLShader();
	
		bool loadFromFiles(std::string vertFile, std::string fragFile);
		void enable();
		void disable();
		
		void setMVP(glm::mat4 mvpMat);
	};
}

#endif
