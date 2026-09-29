#include "file_handler.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

void handleFiles(std::string& currentPathStr, std::string& main, ProgramConfig& config, StringList& csvFiles) {
	fs::path currentPath(currentPathStr);

	if (csvFiles.size() == 0) {
		std::cout << "No .csv file was found in this directory ...\n";
		std::exit(0);
	}

	auto logFilePath = currentPathStr + "/activity_log.txt";
	std::ofstream logFile(logFilePath);
	if (!logFile.is_open()) {
		std::cerr << "Could not open \n'"
				  << logFilePath
				  << "'\n Please contact the designer of this program\n";
		std::exit(1);
	} else {
		logFile << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
		logFile << "=-= ActAn - Activity Measurements log =-=\n";
		logFile << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";
		logFile.close();
	}

	// flags for python scripts
	std::string flags;
	flags = " --area_no " + std::to_string(config.area_no);
	flags += " --tframe_run " + std::to_string(config.tframe_run);
	flags += " --thresh " + std::to_string(config.thresh);
	flags += " --epsilon " + std::to_string(config.epsilon);
	flags += " --vol_cuvette " + std::to_string(config.vol_cuvette);

	for (auto& file : csvFiles) {
		fs::path filePath(file);
		auto relFile = fs::relative(filePath, currentPath).string();

		auto command = "python3 " + main + " --file \"" + file + "\"" + flags;
		std::cout << "Starting analysis for file '"
				  << relFile << "' ...\n";
		std::system(command.c_str());

		auto jsonFilePath = currentPathStr + "/temp_result.json";
		std::ifstream jsonFile(jsonFilePath);

		if (jsonFile.is_open()) {
			try {
				auto res = nlohmann::json::parse(jsonFile);
				jsonFile.close();

				auto slope = res["slope"];
				auto v = res["v"];

				std::ofstream logFile(logFilePath, std::ios::app);
				if (logFile.is_open()) {
					logFile << "file:        " << relFile << "\n";
					logFile << "slope:       " << slope << "\n";
					logFile << "v:           " << v << "\n";
					logFile << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
					logFile.close();
				} else {
					std::cerr << "Error: could not open log file\n";
					std::exit(1);
				}

				std::cout << "Analysis successful!\n-\n";

			
			} catch (const nlohmann::json::parse_error& e) {
				std::cerr << "Error parsing the temp_result.json file\n"
						  << e.what() << "\n";
				std::exit(1);
			}

			std::remove(jsonFilePath.c_str());
		} else {
			std::cerr << "Error: No temp_result.json file was generated\n";
			std::exit(1);
		}
	}

	std::cout << "All analysis have been done. You can find your "
			  << "results in 'activity_log.txt\n";
}
