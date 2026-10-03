#include "file_handler.h"
#include "file_searcher.h"
#include "dispatcher.h"
#include "json_reader.h"
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	auto exe_path = fs::absolute(argv[0]);
	auto project_path = exe_path.parent_path().parent_path();

	auto main_path = project_path / "scripts" / "main.py";
	auto config_file_path = project_path / "config" / "config.json";
	auto current_path = fs::current_path().string();

	auto main_str = main_path.string();
	auto config_file_str = config_file_path.string();

	// load config.json file
	auto p_config = loadConfigFile(config_file_str);

	// load flag values
	FlagConfig f_config;

	// Run dispatcher
	StringList args;
	for (auto i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}
	dispatch(args, p_config, f_config);

	// collect files and manipulate them
	auto csvFiles = findCsvFiles(current_path);
	handleFiles(current_path, main_str, p_config, f_config, csvFiles);

	return 0;
}
