#include "file_handler.h"
#include "file_searcher.h"
#include <iostream>
#include <cstdlib>

namespace fs = std::filesystem;

int main() {
	auto current_path = fs::current_path().string();
	FileList csvFiles = findCsvFiles(current_path);

	if (csvFiles.size() == 0) {
		std::cout << "No .csv file was found in this directory ...\n";
	}

	for (auto& file : csvFiles) {
		std::string command = "python3 scripts/main.py --file " + file;
		std::system(command.c_str());
	}
	return 0;
}
