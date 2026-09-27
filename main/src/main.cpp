#include "file_handler.h"
#include "file_searcher.h"
#include "dispatcher.h"
#include <iostream>
#include <cstdlib>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	auto exe_path = fs::absolute(argv[0]);
	auto main = exe_path.parent_path().parent_path().string() + "/scripts/main.py";
	auto current_path = fs::current_path().string();

	std::vector<std::string> args;
	for (auto i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}

	dispatch(args);

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
