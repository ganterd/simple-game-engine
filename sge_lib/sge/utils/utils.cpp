#include "utils.hpp"

namespace SGE
{
	const char* Utils::readFile(const char* filePath){
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
}
