#ifndef _MODULES_H
#define _MODULES_H

#include "modules/latex/latex.h"
#include "modules/java/java.h"
#include "modules/cpp/cpp.h"


#define __MODULE__(name) \
else if(::strcmp(pkg, #name) == 0) \
	done = ::name(optionNb, options);
	
	
#define MODULES \
	__MODULE__(latex) \
	__MODULE__(java) \
	__MODULE__(cpp) \

	
#endif
