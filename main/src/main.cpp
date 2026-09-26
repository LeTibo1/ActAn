#include "file_handler.h"
#include "file_searcher.h"
#include <iostream>
#include <cstdlib>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	fs::path exe_path = fs::absolute(argv[0]);
	auto main = exe_path.parent_path().parent_path().string() + "/scripts/main.py";

	std::string current_path;
	if (argc > 1) {
		current_path = argv[1];
	} else {
		current_path = fs::current_path().string();
	}

	FileList csvFiles = findCsvFiles(current_path);

	if (csvFiles.size() == 0) {
		std::cout << "No .csv file was found in this directory ...\n";
	}

	for (auto& file : csvFiles) {
		std::string command = "python3 " + main + " --file \"" + file + "\"";
		std::system(command.c_str());
	}
	return 0;
}
