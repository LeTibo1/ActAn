#pragma once
#include "types.h"
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

std::string baseName(const std::string& s);
std::string removeExt(const std::string& s);
std::string generatePythonFlags(ProgramConfig& p_config, FlagConfig& f_config);
StringSet getRelSubDirectories(fs::path& currentPath, StringList& csvFiles);
std::string generatePythonCommand(std::string& main, std::string& file, std::string& flags);
nlohmann::json readJsonFile(fs::path& currentPath);
std::map<std::string, double> getMeanValues(std::map<std::string, std::vector<double>>& values_map);

void handleFiles(
		std::string& currentPathStr, std::string& main,
		ProgramConfig& p_config, FlagConfig& f_config,
		StringList& csvFiles);
