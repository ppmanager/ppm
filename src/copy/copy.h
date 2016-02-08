#ifndef _COPY_H
#define _COPY_H

#define COPY_FOLDERS_AND_FILES 1


#include "General.h"
#include <fstream>
#include <cstring>
#include <list>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>

#if OS == WIN
	#include <windows.h>
	#include <tchar.h>
	#include <stdio.h>
	#include <direct.h>
#else
#endif

void copyFile(const char* from, const char* to);
void copyRootFolder(const char* folderName, const char* to);
void copyFolder(const char* from, const char* to);
void listAllFiles(const char* path, const char* preStr);

#endif
