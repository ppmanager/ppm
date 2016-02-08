#ifndef _DEFAULT_GENERAL_H
#define	_DEFAULT_GENERAL_H

#include "src/OS.h"
#include "src/Debug.h"

#include "src/Types.h"
#include <stdio.h>

#include "src/Printer.h"

extern bool existsAlready;
extern char* prjName;
extern char* appRoot;

bool newProjectRequired();
void projectCreatedRequired();

#endif	/* _DEFAULT_GENERAL_H */

