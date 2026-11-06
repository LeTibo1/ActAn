#include "logFile_handler.h"
#include <fstream>
#include <sstream>
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
		logFile << "-----------------------------------------\n";
		logFile << "        FILE       |    v     | comments\n";
		logFile << "-----------------------------------------\n";
		logFile.close();
	}

	return logFilePath;
}

void append2LogFile(
		fs::path& logFilePath, std::string& relFile,
		nlohmann::json& res, FlagConfig& f_config,
		StringSet& dirs
		) {
	auto v = res["v"].get<double>();

	std::ofstream logFile(logFilePath, std::ios::app);
	if (logFile.is_open()) {
		// sort different sub directories
		auto dir = fs::path(relFile).parent_path().string();
		auto it = dirs.find(dir);
		if (it != dirs.end()) {
			logFile << "\nSub-Directory: " << dir << "\n";
			logFile << "-----------------------------------------\n";

			dirs.erase(it);
		}
		auto file = fs::path(relFile).stem().string();

		// comment for dosage if it is in the right area
		std::string comment;
		if (f_config.dosage) {
			if (v >= 54 && v <= 64) comment = "Right";
			if (v < 54) comment = "Too low: more GR";
			if (v > 64) comment = "Too high: more H2O:EtOH";
		}

		// get file to a certain length for table
		int size = 0;
		for (unsigned char c : file) {
			if ((c & 0xC0) == 0x80) continue;
			if (c == 0xCC || c == 0xCD) continue;
			++size;
		}
		if (size < 19) {
			int n = 19 - size;
			file += std::string(n, ' ');
		}

		// same for v
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(4) << v;
		auto v_str = oss.str();

		if (v_str.size() < 8) {
			int n = 8 - v_str.size();
			v_str += std::string(n, ' ');
		}

		logFile << file << "| " << v_str << " | " << comment << "\n";
		logFile.close();
	} else {
		std::cerr << "Error: could not open log file\n";
		std::exit(1);
	}
}
