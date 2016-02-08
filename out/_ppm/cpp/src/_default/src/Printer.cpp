#include "Printer.h"

static std::ostream* ___output = 0;

#ifdef __MUTEX_LIB_INCLUDED__
#include "_libs/mutex/mutex.h"
static ::Mutex mutex;
::Mutex& getOutputMutex()
{
	return mutex;
}
#endif

std::ostream& getOutput()
{
	if(___output == 0)
		___output = &std::cout;
	
    return *___output;
}

std::ostream& setOutput(std::ostream* output)
{
	___output = output;
}