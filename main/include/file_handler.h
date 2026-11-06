#pragma once
#include "types.h"
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

void handleFiles(
		std::string& currentPathStr, std::string& main,
		ProgramConfig& p_config, FlagConfig& f_config,
		StringList& csvFiles);
