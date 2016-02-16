#include "General.h"
#include <fstream>
#include <cstring>
#include <list>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>

#include "modules.h"

bool existsAlready;
char* prjName;
char* appRoot;


bool newProjectRequired()
{
	if(existsAlready)
	{
		getOutput() << "Project \"" << prjName << "\" already exists.";
		return false;
	}
	
	return true;
}

void projectCreatedRequired()
{
	if(::strcmp(prjName, ".") == 0)
	{
		existsAlready = true;
		return;
	}
	
	struct stat info;
	existsAlready = !stat(prjName, &info);
	if(!existsAlready)
		_mkdir(prjName);
	
	_chdir(prjName);
}

int main(int argc, char* argv[])
{
	bool displayHelp = true;
	bool done = false;
	
	appRoot = argv[0];
	signed int appRootSize = strlen(appRoot) - 1;
	while(appRootSize >= 0 && appRoot[appRootSize] != '\\' && appRoot[appRootSize] != '/')
		--appRootSize;
	if(appRootSize >= 0)
		appRoot[appRootSize] = '\0';
	
	argv++;
	argc -= 1;
	
	if(argc >= 2)
	{
		char* pkg = argv[0];
		prjName = argv[1];
		int optionNb = argc - 2;
		char** options = argv + 2;
		
		int pkgSize = ::strlen(pkg);
		for(int i = 0; i < pkgSize; ++i)
			pkg[i] = ::tolower(pkg[i]);
		
		displayHelp = false;
		
		config.load();
		
		if(false);
			MODULES
		else 
			displayHelp = true;
	}
	
	if(displayHelp)
	{ // Error or help required
		getOutput() << "Usage : ppm <package_name> <project_name> [<package_options>]" << std::endl;
		getOutput() << "Usage : ppm <package_name> . [<package_options>]" << std::endl;
		getOutput() << "Packages :" << std::endl;
		MODULES_HELP
	}
	else if(done)
	{ // Well created the package
		getOutput() << "Project \"" << prjName << "\" created/edited or help viewed." << std::endl;
	}
	else
	{ // An error occured while installing the package
		getOutput() << "An error occured." << std::endl;
	}
	
	return 0;
}

