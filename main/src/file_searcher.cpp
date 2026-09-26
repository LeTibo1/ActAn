#include "file_searcher.h"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

FileList findCsvFiles(const std::string& start_path) {
	FileList foundFiles;

	for (const auto& entry : fs::recursive_directory_iterator(start_path) {
		if (entry.is_regular_file() && entry.path().extension() == ".csv") {
			foundFiles.pushback(entry.path().string());
		}
	}

	return foundFiles;
}
