#pragma once
#include "types.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

std::ofstream createLogFile(const fs::path& currentPath, FlagConfig& f_config);

void append2LogFile(
		std::ostream& out,
		Measurement& entry,
		FlagConfig& f_config,
		StringSet& dirs);

void appendMean2LogFile(std::ostream& out, double& mean);
void terminationMessage2LogFile(std::ostream& out);
