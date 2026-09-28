#include "file_handler.h"
#include <iostream>
#include <cstdlib>

void handleFiles(std::string& main, ProgramConfig& config, StringList& csvFiles) {
	if (csvFiles.size() == 0) {
		std::cout << "No .csv file was found in this directory ...\n";
		std::exit(0);
	}

	// flags for python scripts
	std::string flags;
	flags = " --area_no " + std::to_string(config.area_no);
	flags += " --tframe_run " + std::to_string(config.tframe_run);
	flags += " --thresh " + std::to_string(config.thresh);
	flags += " --epsilon " + std::to_string(config.epsilon);
	flags += " --vol_cuvette " + std::to_string(config.vol_cuvette);

	for (auto& file : csvFiles) {
		auto command = "python3 " + main + " --file \"" + file + "\"" + flags;
		std::system(command.c_str());
	}
}
