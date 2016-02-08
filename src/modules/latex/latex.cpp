#include "latex.h"


bool latex(int argc, char* argv[])
{
	if(!newProjectRequired())
		return false;
	
	bool help = false;
	
	for(int i = 0; i < argc; ++i)
	{
		if(::strcmp(argv[i], "-h") == 0)
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
		return true;
	}
	
	projectCreatedRequired();
	
	copyRootFolder("_ppm\\latex", ".");
	
	return true;
}
