#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "General.h"
#include "copy/copy.h"

#define CONFIG_SAVE_FILE "configuration.conf"

class Config
{
public:
	char vcPath[255];
	
	bool save();
	bool load();
};

extern Config config;

bool settings(int argc, char* argv[]);


#endif