#pragma once

#ifdef WIN32
	#ifdef sge_lib_EXPORTS
		#define Export __declspec( dllexport )  
	#else
		#define Export __declspec( dllimport )  
	#endif
#else
	#define Export
#endif