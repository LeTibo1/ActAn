#include "help.h"
#include <iostream>

ParseAction printHelp() {
	std::cout << "HELP\n";
	return ParseAction::Return;
}
