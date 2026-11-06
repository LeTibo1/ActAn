#include "logFile_handler.h"
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
		writeBanner(logFile);
		logFile << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
		logFile << "=-=-=-=-=-=    Activity Measurements log    =-=-=-=-=-=\n";
		logFile << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";
		logFile << "-------------------------------------------------------\n";
		logFile << "          FILE          |     v      |    comments     \n";
		logFile << "-------------------------------------------------------\n";
		logFile.close();
	}

	return logFilePath;
}

void writeBanner(std::ostream& out) {
    out << R"ART(
                _        _      _
               / \   ___| |_   / \   _ __
              / _ \ / __| __| / _ \ | '_ \
             / ___ \ (__| |_ / ___ \| | | |
            /_/   \_\___|\__/_/   \_\_| |_|
)ART";
    out << "\n";
}

void append2LogFile(
		fs::path& logFilePath,
		Measurement& entry,
		FlagConfig& f_config,
		StringSet& dirs
		) {

	auto v = entry.value;
	auto relFile = entry.file;
	auto name = entry.name;

	std::ofstream logFile(logFilePath, std::ios::app);
	if (logFile.is_open()) {
		// sort different sub directories
		auto dir = fs::path(relFile).parent_path().string();
		auto it = dirs.find(dir);
		if (it != dirs.end()) {
			logFile << "\nSub-Directory: " << dir << "\n";
			logFile << "-------------------------------------------------------\n";

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
		if (size < 24) {
			int n = 24 - size;
			file += std::string(n, ' ');
		}

		// same for v
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(4) << v;
		auto v_str = oss.str();

		if (v_str.size() < 10) {
			int n = 10 - v_str.size();
			v_str += std::string(n, ' ');
		}

		logFile << file << "|  " << v_str << "| " << comment << "\n";
		logFile.close();
	} else {
		std::cerr << "Error: could not open log file\n";
		std::exit(1);
	}
}

void appendMean2LogFile(fs::path& logFilePath, double& mean) {
	std::ofstream logFile(logFilePath, std::ios::app);
	if (logFile.is_open()) {
		// format mean
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(4) << mean;
		auto mean_str = oss.str();

		logFile << "                        --------------\n";
		logFile << "    ==> Mean Value:        " << mean_str << "\n\n";
		logFile.close();
	} else {
		std::cerr << "Error: could not open log file\n";
		std::exit(1);
	}
}

void terminationMessage2LogFile(fs::path& logFilePath) {
	std::ofstream logFile(logFilePath, std::ios::app);
	if (logFile.is_open()) {
		logFile << "\n\n-------------------------------------------------------\n";
		logFile << "Disclaimer: The values are provided without warranty.\n"
				<< "Please interpret the results with caution and verify\n"
				<< "the generated plots to confirm that the correct region\n"
				<< "was interpolated. If it was not, please contact the\n"
				<< "developer of this program or perform the analysis\n"
				<< "manually.\n";
		logFile << "-------------------------------------------------------\n";
		logFile.close();
	} else {
		std::cerr << "Error: could not open log file\n";
		std::exit(1);
	}
}
