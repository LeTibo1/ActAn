#include "file_handler.h"
#include <iostream>
#include <cstdlib>



void handleFiles(std::string& main, StringList& csvFiles) {
	if (csvFiles.size() == 0) {
		std::cout << "No .csv file was found in this directory ...\n";
	}

	for (auto& file : csvFiles) {
		std::string command = "python3 " + main + " --file \"" + file + "\"";
		std::system(command.c_str());
	}
}
