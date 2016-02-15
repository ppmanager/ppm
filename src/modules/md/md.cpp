#include "md.h"

#define MD_COMPILER_UNKOWN 0
#define MD_COMPILER_GCC 1
#define MD_COMPILER_CL 2

static bool addRootFiles(int compiler, const char* makefileType);
static bool addLibraries(std::list<char*>& libraries);
static int getCompiler(char* makefileType);
static bool showPackageDetecting();
static bool detectInstallation();
static bool helpCompilers();
static bool helpLibs();
static bool showHelp();


static bool showHelp()
{
	getOutput() << "Help :" << std::endl;
	getOutput() << " -h             : Display this help" << std::endl;
	getOutput() << " -c<name>       : Define the compiler" << std::endl;
	getOutput() << " -hc            : Display the list of supported compilers" << std::endl;
	getOutput() << " -hl            : Display the list of libraries" << std::endl;
	getOutput() << " -u -upgrade    : Upgrade the current project with new addons" << std::endl;
	getOutput() << " -l<name>       : Add a library" << std::endl;
	getOutput() << " -e             : Detect if the package is installed" << std::endl;
	return true;
}

bool md(int argc, char* argv[])
{
	bool help = false;
	bool helpLib = false;
	bool helpCompiler = false;
	bool packageDetecting = false;
	std::list<char*> libraries;
	std::map<char, bool> options;
	
	char* makefileType = 0;
	
	options.emplace('u', false); // upgrade
	
	for(int i = 0; i < argc; ++i)
	{
		if(::strncmp(argv[i], "-l", 2) == 0)
			libraries.emplace_back(argv[i] + 2);
		else if(::strncmp(argv[i], "-c", 2) == 0)
			makefileType = argv[i] + 2;
		else if(::strcmp(argv[i], "-hl") == 0)
			helpLib = true;
		else if(::strcmp(argv[i], "-hc") == 0)
			helpCompiler = true;
		else if(::strcmp(argv[i], "-e") == 0)
			packageDetecting = true;
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
		return showHelp();
	
	if(helpLib)
		return helpLibs();
	
	if(helpCompiler)
		return helpCompilers();
	
	if(packageDetecting)
		return showPackageDetecting();
	
	projectCreatedRequired();
	
	if(!options['u'])
	{ // Add root files
		if(!makefileType)
		{
			getOutput() << "/!\\ Makefile type not defined!" << std::endl;
			return false;
		}
		
		if(!addRootFiles(getCompiler(makefileType), makefileType))
			return false;
	}
	
	return addLibraries(libraries);
}


static bool detectInstallation()
{
	struct stat info;
	return !stat("doc\\md", &info);
}

static int getCompiler(char* makefileType)
{
	int compilerSize = ::strlen(makefileType);
	for(int i = 0; i < compilerSize; ++i)
		makefileType[i] = ::tolower(makefileType[i]);
	
	if(::strcmp(makefileType, "gcc") ||
	   ::strcmp(makefileType, "g++") ||
	   ::strcmp(makefileType, "mingw"))
		return MD_COMPILER_GCC;
	else if(::strcmp(makefileType, "cl"))
		return MD_COMPILER_CL;
	
	return MD_COMPILER_UNKOWN;
}


static bool addRootFiles(int compiler, const char* makefileType)
{
	if(compiler == MD_COMPILER_UNKOWN)
	{
		getOutput() << "/!\\ Unkown compiler \"" << makefileType << "\"." << std::endl;
		return false;
	}
	
	if(detectInstallation())
	{
		getOutput() << "/!\\ Package already installed. Use -upgrade to add libraries." << std::endl;
		return false;
	}
	
	getOutput() << "Adding root" << std::endl;
	copyRootFolder("_ppm\\md", ".");
	
	char srcMakefile[100 + 2 + ::strlen(appRoot)];
	const char* destMakefile;
	
	switch(compiler)
	{
		case MD_COMPILER_GCC:
			sprintf(srcMakefile, "%s\\%s", appRoot, "_ppm\\md_\\_gcc_makefile.addon");
			destMakefile = "_makefile";
			break;
		
		case MD_COMPILER_CL:
			sprintf(srcMakefile, "%s\\%s", appRoot, "_ppm\\md_\\_cl_makefile.addon");
			destMakefile = "makefile";
			break;
	}
	
	std::ifstream srcMakefileStream(srcMakefile, std::ios::binary);
	std::ofstream makefileStream(destMakefile, std::ios::binary | std::ios::app);
	makefileStream << srcMakefileStream.rdbuf();
	makefileStream.close();
	srcMakefileStream.close();
	
	return true;
}


static bool addLibraries(std::list<char*>& libraries)
{
	char libPath[100] = "_ppm\\md_libs\\";
	char destLibPath[100] = ".\\doc\\md\\";
	char* libPathSub = libPath + ::strlen(libPath);
	char* destLibPathSub = destLibPath + ::strlen(destLibPath);
	for(auto& lib : libraries)
	{
		getOutput() << "Adding library " << lib << std::endl;
		::sprintf(libPathSub, "%s", lib);
		::sprintf(destLibPathSub, "%s", lib);
		copyRootFolder(libPath, destLibPath);
	}
	
	return true;
}

static bool helpLibs()
{
	char path[strlen(appRoot) + strlen("_ppm\\md_libs\\*") + 2];
	sprintf(path, "%s\\_ppm\\md_libs\\*", appRoot);
	
	getOutput() << "List of libraries :" << std::endl;
	listAllFiles(path, " * ");
	return true;
}

static bool helpCompilers()
{
	getOutput() << "List of supported compilers :" << std::endl;
	getOutput() << " * GCC" << std::endl;
	getOutput() << " * MinGW" << std::endl;
	getOutput() << " * CL" << std::endl;
	return true;
}

static bool showPackageDetecting()
{
	if(detectInstallation())
		getOutput() << "The package is already installed." << std::endl;
	else
		getOutput() << "The package is not installed yet." << std::endl;
	return true;
}

