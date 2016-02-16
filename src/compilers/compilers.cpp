#include "compilers.h"
#include "General.h"
#include "copy/copy.h"
#include <fstream>
#include <cstring>
#include <list>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>

int getCompiler(char* compiler)
{
	int compilerSize = ::strlen(compiler);
	for(int i = 0; i < compilerSize; ++i)
		compiler[i] = ::tolower(compiler[i]);
	
	if(::strcmp(compiler, "gcc") == 0 ||
	   ::strcmp(compiler, "g++") == 0)
		return COMPILER_GCC;
	else if(::strcmp(compiler, "mingw") == 0)
		return COMPILER_MINGW;
	else if(::strcmp(compiler, "cl") == 0)
		return COMPILER_CL;
	
	return COMPILER_UNKOWN;
}

bool helpCompilers()
{
	getOutput() << "List of supported compilers :" << std::endl;
	getOutput() << " * MinGW" << std::endl;
	getOutput() << " * GCC" << std::endl;
	getOutput() << " * CL" << std::endl;
	return true;
}

bool helpLibs(const char* path)
{
	char p[::strlen(appRoot) + ::strlen(path) + 4];
	sprintf(p, "%s\\%s\\*", appRoot, path);
	
	getOutput() << "List of libraries :" << std::endl;
	listAllFiles(p, " * ");
	return true;
}
