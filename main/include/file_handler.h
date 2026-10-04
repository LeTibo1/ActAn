#pragma once
#include "types.h"
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

fs::path createLogFile(fs::path& currentPath);
std::string generatePythonFlags(ProgramConfig& p_config, FlagConfig& f_config);
std::string generatePythonCommand(std::string& main, std::string& file, std::string& flags);
nlohmann::json readJsonFile(fs::path& currentPath);
void append2LogFile(fs::path& logFilePath, std::string& relFile, nlohmann::json& res, FlagConfig& f_config);

void handleFiles(
		std::string& currentPathStr, std::string& main,
		ProgramConfig& p_config, FlagConfig& f_config,
		StringList& csvFiles
);
