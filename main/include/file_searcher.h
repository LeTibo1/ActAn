#pragma once
#include <string>
#include <vector>
#include <filesystem>

using FileList = std::vector<std::string>;

FileList findCsvFiles(const std::string& start_path);
