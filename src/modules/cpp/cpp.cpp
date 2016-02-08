#include "cpp.h"


bool cpp(int argc, char* argv[])
{
	bool help = false;
	bool helpLib = false;
	std::list<char*> libraries;
	std::map<char, bool> options;
	
	options.emplace('u', false); // upgrade
	
	for(int i = 0; i < argc; ++i)
	{
		if(::strncmp(argv[i], "-l", 2) == 0)
			libraries.emplace_back(argv[i] + 2);
		else if(::strcmp(argv[i], "-hl") == 0)
			helpLib = true;
		else if(::strcmp(argv[i], "-u") == 0 ||
				::strcmp(argv[i], "-upgrade") == 0)
			options['u'] = true;
		else if(::strcmp(argv[i], "-h") == 0)
			help = true;
		else
		{
			getOutput() << "Unkown parameter : \"" << argv[i] << "\"" << std::endl;
			help = true;
		}
	}
	
	if(help)
	{
		getOutput() << "Help :" << std::endl;
		getOutput() << " -h             : Display this help" << std::endl;
		getOutput() << " -hl            : Display the list of libraries" << std::endl;
		getOutput() << " -u -upgrade    : Upgrade the current project with new addons" << std::endl;
		getOutput() << " -l<name>       : Add a library" << std::endl;
		return true;
	}
	
	if(helpLib)
	{
		char path[strlen(appRoot) + strlen("_ppm\\cpp_libs\\*") + 2];
		sprintf(path, "%s\\_ppm\\cpp_libs\\*", appRoot);
		
		getOutput() << "List of libraries :" << std::endl;
		listAllFiles(path, " * ");
		return true;
	}
	
	projectCreatedRequired();
	
	if(!options['u'])
	{ // Add root files
		if(!newProjectRequired())
			return false;
		
		getOutput() << "Adding root" << std::endl;
		copyRootFolder("_ppm\\cpp", ".");
		
		std::ofstream projectStream("_project", std::ios::binary | std::ios::app);
		projectStream << std::endl << "OUTPUT_NAME = " << prjName << std::endl;
		projectStream.close();
	}
	
	char libPath[100] = "_ppm\\cpp_libs\\";
	char destLibPath[100] = ".\\src\\_libs\\";
	char* libPathSub = libPath + strlen(libPath);
	char* destLibPathSub = destLibPath + strlen(destLibPath);
	for(auto& lib : libraries)
	{
		getOutput() << "Adding library " << lib << std::endl;
		sprintf(libPathSub, "%s", lib);
		sprintf(destLibPathSub, "%s", lib);
		copyRootFolder(libPath, destLibPath);
	}
	
	return true;
}
