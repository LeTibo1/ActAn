#pragma once
#include "types.h"
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

fs::path createLogFile(fs::path& currentPath);

void append2LogFile(
		fs::path& logFilePath, std::string& relFile,
		nlohmann::json& res, FlagConfig& f_config,
		StringSet& dirs);
