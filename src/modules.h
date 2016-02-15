#ifndef _MODULES_H
#define _MODULES_H

#include "modules/licence/licence.h"
#include "modules/latex/latex.h"
#include "modules/java/java.h"
#include "modules/cpp/cpp.h"
#include "modules/cs/cs.h"
#include "modules/md/md.h"


#define __MODULE__(name) \
else if(::strcmp(pkg, #name) == 0) \
	done = ::name(optionNb, options);
	
	
#define __MODULE_HELP__(name) \
	getOutput() << " * "#name << std::endl;
	
	
#define MODULES \
	__MODULE__(licence) \
	__MODULE__(latex) \
	__MODULE__(java) \
	__MODULE__(cpp) \
	__MODULE__(cs) \
	__MODULE__(md) \
	

#define MODULES_HELP \
	__MODULE_HELP__(licence) \
	__MODULE_HELP__(latex) \
	__MODULE_HELP__(java) \
	__MODULE_HELP__(cpp) \
	__MODULE_HELP__(cs) \
	__MODULE_HELP__(md) \
	
#endif
