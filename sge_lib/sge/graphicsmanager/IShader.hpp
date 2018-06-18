#ifndef SGE_ISHADER_HPP
#define SGE_ISHADER_HPP

#ifndef SGE_MVP_SHADER_MAT
#define SGE_MVP_SHADER_MAT "modelViewProjection"
#endif

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <glm/glm.hpp>

namespace SGE
{
	class IShader
	{
	public:
		
		virtual bool loadFromFiles(std::string vertFile, std::string fragFile) = 0;
		virtual void enable() = 0;
		virtual void disable() = 0;
		
		virtual void setMVP(glm::mat4 mvpMat) = 0;
		
		const char* readFile(const char* filePath){
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
	};
}

#endif
