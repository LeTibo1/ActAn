#pragma once
#include "types.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

fs::path createLogFile(fs::path& currentPath);
void writeBanner(std::ostream& out);

void append2LogFile(
		fs::path& logFilePath,
		Measurement& entry,
		FlagConfig& f_config,
		StringSet& dirs);

void appendMean2LogFile(fs::path& logFilePath, double& mean);
void terminationMessage2LogFile(fs::path& logFilePath);
