#include "cpp.h"
#include "compilers/compilers.h"
#include "modules/settings/settings.h"

static bool addRootFiles(int compiler, const char* strCompiler);
static bool addLibraries(std::list<char*>& libraries);
static bool showPackageDetecting();
static bool helpLibs();
static bool showHelp();


static bool showHelp()
{
	getOutput() << "Help :" << std::endl;
	getOutput() << " -h             : Display this help" << std::endl;
	getOutput() << " -hl            : Display the list of libraries" << std::endl;
	getOutput() << " -hc            : Display the list of supported compilers" << std::endl;
	getOutput() << " -c<name>       : Define the compiler" << std::endl;
	getOutput() << " -u -upgrade    : Upgrade the current project with new addons" << std::endl;
	getOutput() << " -l<name>       : Add a library" << std::endl;
	getOutput() << " -e             : Detect if the package is installed" << std::endl;
	return true;
}

bool cpp(int argc, char* argv[])
{
	bool help = false;
	bool helpLib = false;
	bool helpCompiler = false;
	bool packageDetecting = false;
	std::list<char*> libraries;
	std::map<char, bool> options;
	char* compiler = 0;
	
	options.emplace('u', false); // upgrade
	
	for(int i = 0; i < argc; ++i)
	{
		if(::strncmp(argv[i], "-l", 2) == 0)
			libraries.emplace_back(argv[i] + 2);
		else if(::strncmp(argv[i], "-c", 2) == 0)
			compiler = argv[i] + 2;
		else if(::strcmp(argv[i], "-hc") == 0)
			helpCompiler = true;
		else if(::strcmp(argv[i], "-hl") == 0)
			helpLib = true;
		else if(::strcmp(argv[i], "-u") == 0 ||
				::strcmp(argv[i], "-upgrade") == 0)
			options['u'] = true;
		else if(::strcmp(argv[i], "-h") == 0)
			help = true;
		else if(::strcmp(argv[i], "-e") == 0)
			packageDetecting = true;
		else
		{
			getOutput() << "Unkown parameter : \"" << argv[i] << "\"" << std::endl;
			help = true;
		}
	}
	
	if(help)
		return showHelp();
	
	if(helpLib)
		return helpLibs("_ppm\\cpp_libs");
	
	if(helpCompiler)
		return helpCompilers();
	
	if(packageDetecting)
		return showPackageDetecting();
	
	if(!options['u'])
	{ // Add root files
		if(!compiler)
		{
			getOutput() << "/!\\ Compiler type not defined!" << std::endl;
			return false;
		}
		
		if(!addRootFiles(getCompiler(compiler), compiler))
			return false;
	}
	
	projectCreatedRequired();
	
	if(!addLibraries(libraries))
		return false;
	
	return true;
}


static bool addRootFiles(int compiler, const char* strCompiler)
{
	if(compiler == COMPILER_UNKOWN)
	{
		getOutput() << "/!\\ Unkown compiler \"" << strCompiler << "\"." << std::endl;
		return false;
	}
	
	if(compiler == COMPILER_CL && ::strlen(config.vcPath) == 0)
	{
		getOutput() << "/!\\ Undefined setting vcPath." << std::endl;
		return false;
	}
	
	projectCreatedRequired();
	if(!newProjectRequired())
		return false;
	
	getOutput() << "Adding root" << std::endl;
	copyRootFolder("_ppm\\cpp", ".");
	
	
	char srcMakefile[100 + 2 + ::strlen(appRoot)];
	
	switch(compiler)
	{
		case COMPILER_MINGW:
		case COMPILER_GCC:
			copyRootFolder("_ppm\\cpp_\\gcc", ".");
			break;
		
		case COMPILER_CL:
			copyRootFolder("_ppm\\cpp_\\cl", ".");
			break;
	}
	
	
	std::ofstream projectStream("_project", std::ios::binary | std::ios::app);
	projectStream << std::endl << "OUTPUT_NAME = " << prjName << std::endl;
	switch(compiler)
	{
		case COMPILER_MINGW:
		case COMPILER_GCC:
			projectStream << std::endl << "VC_PATH = " << config.vcPath << std::endl;
			break;
		
		case COMPILER_CL:
			break;
	}
	projectStream.close();
	
	return true;
}


static bool addLibraries(std::list<char*>& libraries)
{
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

static bool showPackageDetecting()
{
	if(existsAlready)
		getOutput() << "The package is already installed." << std::endl;
	else
		getOutput() << "The package is not installed yet." << std::endl;
	return true;
}
