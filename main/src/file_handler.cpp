#include "file_handler.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <sys/wait.h>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

void handleFiles(
		std::string& currentPathStr, std::string& main,
		ProgramConfig& p_config, FlagConfig& f_config,
		StringList& csvFiles
) {
	fs::path currentPath(currentPathStr);

	if (csvFiles.size() == 0) {
		std::cout << "No .csv file was found in this directory ...\n";
		std::exit(0);
	}

	auto logFilePath = currentPath / "activity_log.txt";
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
	flags = " --area_no " + std::to_string(p_config.area_no);
	flags += " --tframe_run " + std::to_string(p_config.tframe_run);
	flags += " --thresh " + std::to_string(p_config.thresh);
	flags += " --epsilon " + std::to_string(p_config.epsilon);
	flags += " --vol_cuvette " + std::to_string(p_config.vol_cuvette);
	flags += " --is_dosage " + std::to_string(f_config.dosage);

	for (auto& file : csvFiles) {
		fs::path filePath(file);
		auto relFile = fs::relative(filePath, currentPath).string();

		#ifdef _WIN32
			std::string pythonCmd = "python";
		#else
			std::string pythonCmd = "python3";
		#endif
		auto command = pythonCmd + " \"" + main + "\" --file \"" + file + "\" " + flags;
		std::cout << "Starting analysis for file '"
				  << relFile << "' ...\n";

		int status = std::system(command.c_str());
		int code = WEXITSTATUS(status);
		if (code != 0) {
			std::cerr << relFile << " could not be analyzed. Continue with next file\n-\n";
			continue;
		}

		auto jsonFilePath = currentPath / "temp_result.json";
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
					if (f_config.dosage) {
						std::string result;
						if (v >= 54 && v <= 64) result = "Right!";
						if (v < 54) result = "Too low --> more GR";
						if (v > 64) result = "Too high --> more H2O:EtOH";
						logFile << "v:           " << v << " --> " << result << "\n";
					} else {
						logFile << "v:           " << v << "\n";
					}
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
			  << "results in 'activity_log.txt' and the generated "
			  << "plots in the plots/ folder.\n";
}
