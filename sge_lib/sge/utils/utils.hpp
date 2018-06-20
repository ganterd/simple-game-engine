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
		static const char* readFile(const char* filePath);
		static el::base::type::StoragePointer getELStorage();
	};
}

#endif
