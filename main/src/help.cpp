#include "help.h"
#include <iostream>

ParseAction printHelp() {
	auto message = {
		"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=",
		"=-= Faciliate the analysis of the activity measurements =-=",
		"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=",
		"Usage: actan [OPTIONS]",
		"",
		"Options:",
		"  -h, --help          show this help message",
	};

	for (const auto& msg : message) {
		std::cout << msg << "\n";
	}
	return ParseAction::Return;
}
