#include "logFile_handler.h"
#include <sstream>
#include <iostream>

namespace {
	void writeBanner(std::ostream& out);
	std::string getDosageComment(double v);
	void editStringLength(std::string& s, const int& i);
	std::string editDoubleLength(const double& d, const int& i);
}

namespace {
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

	std::string getDosageComment(double v) {
		if (v < 54) {
			return "Too low: more GR";
		} else if (v > 64) {
			return "Too high: more H2O:EtOH";
		} else {
			return "Right";
		}
	}

	void editStringLength(std::string& s, const int& i) {
		int size = 0;
		for (unsigned char c : s) {
			if ((c & 0xC0) == 0x80) continue;
			if (c == 0xCC || c == 0xCD) continue;
			++size;
		}
		if (size < i) {
			int n = i - size;
			s += std::string(n, ' ');
		}
	}

	std::string editDoubleLength(const double& d, const int& i) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(4) << d;
		auto v_str = oss.str();

		if (v_str.size() < i) {
			int n = i - v_str.size();
			v_str += std::string(n, ' ');
		}

		return v_str;
	}
}

std::ofstream createLogFile(const fs::path& currentPath) {
	// Path of logFile
	auto logFilePath = currentPath / "activity_log.txt";

	std::ofstream logFile(logFilePath);
	if (logFile.is_open()) {
		writeBanner(logFile);
		logFile << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
		logFile << "=-=-=-=-=-=    Activity Measurements log    =-=-=-=-=-=\n";
		logFile << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";
		logFile << "-------------------------------------------------------\n";
		logFile << "          FILE          |     v      |    comments     \n";
		logFile << "-------------------------------------------------------\n";
	} else {
		std::cerr << "Could not open \n'"
				  << logFilePath
				  << "'\n Please contact the designer of this program\n";
		std::exit(1);
	}

	return logFile;
}

void append2LogFile(
		std::ostream& out,
		Measurement& entry,
		FlagConfig& f_config,
		StringSet& dirs
		) {

	auto v = entry.value;
	auto relFile = entry.file;

	// sort different sub directories
	auto dir = fs::path(relFile).parent_path().string();
	auto it = dirs.find(dir);
	if (it != dirs.end()) {
		out << "\nSub-Directory: " << dir << "\n";
		out << "-------------------------------------------------------\n";

		dirs.erase(it);
	}
	auto file = fs::path(relFile).stem().string();

	// comment for dosage if it is in the right area
	std::string comment;
	if (f_config.dosage) {
		comment = getDosageComment(v);
	}

	// get file to a certain length for table
	editStringLength(file, 24);

	// same for v
	auto v_str = editDoubleLength(v, 10);

	// append the entry
	out << file << "|  " << v_str << "| " << comment << "\n";
}

void appendMean2LogFile(std::ostream& out, double& mean) {
	// format mean
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(4) << mean;
	auto mean_str = oss.str();

	out << "                        --------------\n";
	out << "    ==> Mean Value:        " << mean_str << "\n\n";
}

void terminationMessage2LogFile(std::ostream& out) {
	out << "\n\n-------------------------------------------------------\n";
	out << "Disclaimer: The values are provided without warranty.\n"
			<< "Please interpret the results with caution and verify\n"
			<< "the generated plots to confirm that the correct region\n"
			<< "was interpolated. If it was not, please contact the\n"
			<< "developer of this program or perform the analysis\n"
			<< "manually.\n";
	out << "-------------------------------------------------------\n";
}
