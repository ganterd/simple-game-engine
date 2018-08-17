#include "utils.hpp"

// Once off include of easyloggingcc
#include <easylogging++.cc>
INITIALIZE_EASYLOGGINGPP

namespace SGE
{
	const char* Utils::readFile(const char* filePath){
		char* text = nullptr;

		FILE *file = fopen(filePath, "r");

		if (file == NULL)
			return NULL;

		fseek(file, 0, SEEK_END);
		size_t count = ftell(file);
		rewind(file);


		if (count > 0) {
			text = (char*)malloc(sizeof(char) * (count + 1));
			count = fread(text, sizeof(char), count, file);
			text[count] = '\0';
		}
		fclose(file);

		return text;
	}

	el::base::type::StoragePointer Utils::getELStorage()
	{
		return el::base::elStorage;
	}
}
