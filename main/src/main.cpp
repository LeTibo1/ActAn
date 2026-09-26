#include "file_handler.h"
#include "file_searcher.h"
#include <cstdlib>

int main() {
	auto current_path = fs::current_path().string();
	FileList csvFiles = findCsvFiles(current_path);

	for (auto& file : csvFiles) {
		std::string command = "python3 scripts/main.py --file " + file;
		std::system(command.c_str());
	}
	return 0;
}
