#include "copy.h"




void copyFile(const char* from, const char* to)
{
#if COPY_FOLDERS_AND_FILES
	std::ifstream fromStream(from, std::ios::binary);
	std::ofstream toStream(to, std::ios::binary);
	
	toStream << fromStream.rdbuf();
	
	toStream.close();
	fromStream.close();
#endif
}

void copyRootFolder(const char* folderName, const char* to)
{
	char rootFolder[strlen(folderName) + 2 + strlen(appRoot)];
	sprintf(rootFolder, "%s\\%s", appRoot, folderName);
	copyFolder(rootFolder, to);
}

void listAllFiles(const char* path, const char* preStr)
{
	char* fileName;
	bool exit;
	bool skip;
	
#if OS == WIN
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(path, &FindFileData);
	exit = hFind == INVALID_HANDLE_VALUE;
#else
#endif

	while(!exit)
	{
		skip = false;
		
#if OS == WIN
		fileName = FindFileData.cFileName;
#else
#endif

		if(fileName[0] == '.' && (fileName[1] == '\0' || fileName[1] == '.' && fileName[2] == '\0'))
			skip = true;
		
		if(!skip)
		{
			getOutput() << preStr << fileName << std::endl;
		}
		
#if OS == WIN
		if(!FindNextFile(hFind, &FindFileData))
		{
			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
			exit = true;
		}
#else
#endif
	}
}

void copyFolder(const char* from, const char* to)
{
	struct stat info;
	char* fileName;
	char filePath[strlen(from) + 50];
	char* filePathSub;
	char destFilePath[strlen(to) + 50];
	char* destFilePathSub;
	char folderPath[strlen(from) + 2];
	bool isDir;
	bool skip;
	bool exit = false;
	
	sprintf(folderPath, "%s\\*", from);
	sprintf(filePath, "%s\\", from);
	sprintf(destFilePath, "%s\\", to);
	filePathSub = filePath + strlen(filePath);
	destFilePathSub = destFilePath + strlen(destFilePath);

#if COPY_FOLDERS_AND_FILES
	if(stat(to, &info))
		_mkdir(to);
#endif
	
#if OS == WIN
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(folderPath, &FindFileData);
	exit = hFind == INVALID_HANDLE_VALUE;
#else
#endif

	while(!exit)
	{
		skip = false;
		
#if OS == WIN
		fileName = FindFileData.cFileName;
#else
#endif

		if(fileName[0] == '.' && (fileName[1] == '\0' || fileName[1] == '.' && fileName[2] == '\0'))
			skip = true;
		
		if(!skip)
		{
			sprintf(filePathSub, "%s", fileName);
			sprintf(destFilePathSub, "%s", fileName);
		
			if(stat(filePath, &info))
				skip = true; // Error : can't read
			else if(info.st_mode & S_IFDIR)
				isDir = true;
			else
				isDir = false;
			
			if(!skip)
			{
				if(isDir)
					copyFolder(filePath, destFilePath);
				else
					copyFile(filePath, destFilePath);
			}
		}
		
#if OS == WIN
		if(!FindNextFile(hFind, &FindFileData))
		{
			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
			exit = true;
		}
#else
#endif
	}
}

