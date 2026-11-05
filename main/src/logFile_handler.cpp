#include "logFile_handler.h"
#include <fstream>
#include <iostream>

fs::path createLogFile(fs::path& currentPath) {
	// Path of logFile
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

	return logFilePath;
}

void append2LogFile(
		fs::path& logFilePath, std::string& relFile,
		nlohmann::json& res, FlagConfig& f_config,
		StringSet& dirs
		) {
	auto slope = res["slope"];
	auto v = res["v"];

	std::ofstream logFile(logFilePath, std::ios::app);
	if (logFile.is_open()) {
		auto dir = fs::path(relFile).parent_path().string();
		auto it = dirs.find(dir);
		if (it != dirs.end()) {
			logFile << dir << "\n";
			logFile << "=-=-=-=-=\n";

			dirs.erase(it);
		}
		auto file = fs::path(relFile).filename().string();

		logFile << "file:        " << file << "\n";
		//logFile << "slope:       " << slope << "\n";
		if (f_config.dosage) {
			std::string result;
			if (v >= 54 && v <= 64) result = "Right!";
			if (v < 54) result = "Too low --> more GR";
			if (v > 64) result = "Too high --> more H2O:EtOH";
			logFile << "v:           " << v << " --> " << result << "\n";
		} else {
			logFile << "v:           " << v << "\n";
		}
		logFile << "\n----------------------\n";
		logFile.close();
	} else {
		std::cerr << "Error: could not open log file\n";
		std::exit(1);
	}
}
