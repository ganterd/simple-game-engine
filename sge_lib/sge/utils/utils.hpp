#ifndef SGE_UTILS_HPP
#define SGE_UTILS_HPP


#include <easylogging++.h>
#include <iostream>

#include <sge/utils/export.hpp>

namespace SGE
{
	class Export Utils
	{
	public:
		static const char* readFile(const std::string& filePath);
		static const char* readFile(const char* filePath);
		static el::base::type::StoragePointer getELStorage();

		static void splitFilename(const std::string& str, std::string& dir, std::string& file)
		{
			size_t found;
			size_t foundWin32 = str.find_last_of("/\\");
			size_t foundLinux = str.find_last_of("/");
			found = foundWin32 > foundLinux ? foundWin32 : foundLinux;
			dir = str.substr(0, found);
			file = str.substr(found + 1);
		}

		static void printSceneStructure();
	};
}

#endif
