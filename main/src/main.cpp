#include "file_handler.h"
#include "file_searcher.h"
#include "dispatcher.h"
#include "json_reader.h"
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	auto project_path = fs::absolute(argv[0]).parent_path().parent_path();
	auto main = project_path.string() + "/scripts/main.py";
	auto config_file = project_path.string() + "/config/config.json";
	auto current_path = fs::current_path().string();

	// load config.json file
	auto config = loadConfigFile(config_file);

	// Run dispatcher
	StringList args;
	for (auto i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}
	dispatch(args, config);

	// collect files and manipulate them
	auto csvFiles = findCsvFiles(current_path);
	handleFiles(current_path, main, config, csvFiles);

	return 0;
}
