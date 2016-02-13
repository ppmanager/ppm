#include "licence.h"


bool licence(int argc, char* argv[])
{
	bool help = false;
	char* desc = 0;
	char* author = 0;
	char* year = 0;
	
	for(int i = 0; i < argc; ++i)
	{
		if(::strncmp(argv[i], "-y", 2) == 0)
			year = argv[i] + 2;
		else if(::strncmp(argv[i], "-a", 2) == 0)
			author = argv[i] + 2;
		else if(::strncmp(argv[i], "-d", 2) == 0)
			desc = argv[i] + 2;
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
		getOutput() << " Produce a GNU GENERAL PUBLIC LICENCE (GPLv2) in US_en" << std::endl;
		getOutput() << " -h                             : Display this help" << std::endl;
		getOutput() << " -d<description> ; \"-d<...>\"  : Set the description" << std::endl;
		getOutput() << " -a<author>                     : Set the author's name" << std::endl;
		getOutput() << " -y<year>                       : Set the year" << std::endl;
		return true;
	}
	
	if(!desc)
		getOutput() << "/!\\ Description is not set!" << std::endl;
	if(!author)
		getOutput() << "/!\\ Author is not set!" << std::endl;
	if(!year)
		getOutput() << "/!\\ Year is not set!" << std::endl;
	
	if(desc && author && year)
	{
		char licence1Path[strlen(LICENCE_1_PATH) + 2 + strlen(appRoot)];
		sprintf(licence1Path, "%s\\%s", appRoot, LICENCE_1_PATH);
		
		char licence2Path[strlen(LICENCE_2_PATH) + 2 + strlen(appRoot)];
		sprintf(licence2Path, "%s\\%s", appRoot, LICENCE_2_PATH);
		getOutput() << licence2Path << std::endl;
		
		std::ifstream licence1Stream(licence1Path, std::ios::binary);
		std::ifstream licence2Stream(licence2Path, std::ios::binary);
		
		std::ofstream licenceStream("LICENCE", std::ios::binary);
		licenceStream << licence1Stream.rdbuf();
		licenceStream << desc << std::endl;
		licenceStream << "    Copyright (C) ";
		licenceStream << year << "  ";
		licenceStream << author << std::endl;
		licenceStream << licence2Stream.rdbuf();
		licenceStream.close();
		
		licence1Stream.close();
		licence2Stream.close();
		
		return true;
	}
	else
		return false;
}
