#include "settings.h"
#include "General.h"
#include <fstream>
#include <cstring>
#include <list>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>

Config config;

#define CONFIG_TRANSFORM_SYMBOL (char)255
#define CONFIG_TRANSFORM_RMV_SPACE(name)

bool Config::save()
{
	int size;
	int i;
	
	size = ::strlen(config.vcPath);
	for(i = 0; i < size; ++i)
		if(config.vcPath[i] == ' ')
			config.vcPath[i] = CONFIG_TRANSFORM_SYMBOL;
		
	char path[strlen(CONFIG_SAVE_FILE) + strlen(appRoot) + 2];
	sprintf(path, "%s\\%s", appRoot, CONFIG_SAVE_FILE);
	
	std::ofstream configStream(path, std::ios::binary);
	configStream << config.vcPath << " ";
	configStream.close();
}

bool Config::load()
{
	char path[strlen(CONFIG_SAVE_FILE) + strlen(appRoot) + 2];
	sprintf(path, "%s\\%s", appRoot, CONFIG_SAVE_FILE);
	
	struct stat info;
	bool fileExists = !stat(path, &info);
	
	if(fileExists)
	{ // Load from file
		int size;
		int i;
		
		std::ifstream configStream(path, std::ios::binary);
		configStream >> config.vcPath;
		configStream.close();
		
		size = ::strlen(config.vcPath);
		for(i = 0; i < size; ++i)
			if(config.vcPath[i] == CONFIG_TRANSFORM_SYMBOL)
				config.vcPath[i] = ' ';
	}
	else
	{ // Default values
		config.vcPath[0] = '\0';
	}
}


static bool showHelp();


static bool showHelp()
{
	getOutput() << "Help :" << std::endl;
	getOutput() << " -h             : Display this help" << std::endl;
	getOutput() << " -vcpath=<path>  : Path of VC in the Microsoft's SDK" << std::endl;
	getOutput() << " -show:<name>    : Show the value of a setting" << std::endl;
	return true;
}

bool settings(int argc, char* argv[])
{
	bool help = false;
	
	char* vcPath = 0;
	
	std::list<char*> show;
	
	for(int i = 0; i < argc; ++i)
	{
		if(::strncmp(argv[i], "-vcpath=", sizeof("-vcpath=") - 1) == 0)
			vcPath = argv[i] + sizeof("-vcpath=") - 1;
		else if(::strncmp(argv[i], "-show:", sizeof("-show:") - 1) == 0)
			show.emplace_back(argv[i] + sizeof("-show:") - 1);
		else if(::strcmp(argv[i], "-h") == 0)
			help = true;
		else
		{
			getOutput() << "Unkown parameter : \"" << argv[i] << "\"" << std::endl;
			help = true;
		}
	}
	
	if(help)
		return showHelp();
	
	bool save = vcPath;
	
	if(vcPath)
		sprintf(config.vcPath, "%s", vcPath);
	
	
	for(auto& s : show)
	{
		getOutput() << s << " = ";
		
		if(::strcmp(s, "vcpath") == 0)
			getOutput() << config.vcPath;
		else
			getOutput() << "<UNDEFINED>";
		
		getOutput() << std::endl;
	}
	
	if(save)
		config.save();
	
	return true;
}

