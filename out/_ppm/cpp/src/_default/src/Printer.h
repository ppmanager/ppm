#ifndef _DEFAULT_PRINTER_H
#define	_DEFAULT_PRINTER_H

#include <iostream>

#ifdef __MUTEX_LIB_INCLUDED__
	#include "_libs/mutex/mutex.h"
	Mutex& getOutputMutex();
#endif

std::ostream& getOutput();
std::ostream& setOutput(std::ostream* output);

#endif	/* _DEFAULT_PRINTER_H */

