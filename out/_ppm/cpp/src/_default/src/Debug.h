#ifndef _DEFAULT_DEBUG_H
#define	_DEFAULT_DEBUG_H

/*****************************
 * Debug
 * This is managed by the
 * makefile.
 *****************************/
 
#ifdef DEBUG
	#define DEBUG 1
#endif

#if DEBUG
    #define debug(format, ...) { printf(format, ##__VA_ARGS__); fflush(stdout); }
#else
    #define debug(format, ...) ;
#endif

#endif	/* _DEFAULT_DEBUG_H */

