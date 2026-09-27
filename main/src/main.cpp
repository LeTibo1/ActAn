#include "file_handler.h"
#include "file_searcher.h"
#include "dispatcher.h"
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	auto exe_path = fs::absolute(argv[0]);
	auto main = exe_path.parent_path().parent_path().string() + "/scripts/main.py";
	auto current_path = fs::current_path().string();

	// Run dispatcher
	StringList args;
	for (auto i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}
	// exit program if return/error is returned
	auto res = dispatch(args);
	if (res == ParseAction::Return) {
		return 0;
	} else if (res == ParseAction::Error) {
		return 1;
	}

	// collect files and manipulate them
	auto csvFiles = findCsvFiles(current_path);
	handleFiles(main, csvFiles);

	return 0;
}
