#ifndef _COMPILERS_H
#define _COMPILERS_H

#define COMPILER_UNKOWN 0
#define COMPILER_MINGW 1
#define COMPILER_GCC 2
#define COMPILER_CL 3

int getCompiler(char* compiler);
bool helpLibs(const char* path);
bool helpCompilers();
	
#endif
