#include "file_handler.h"
#include "logFile_handler.h"
#include "file_sorter.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/wait.h>

namespace fs = std::filesystem;

std::string baseName(const std::string& s) {
    std::size_t end = s.find_last_not_of("0123456789");
    return (end == std::string::npos) ? s : s.substr(0, end + 1);
}

std::string removeExt(const std::string& s) {
	std::size_t pos = s.find_last_of('.');
	return (pos == std::string::npos) ? s : s.substr(0, pos);
}

std::string generatePythonFlags(ProgramConfig& p_config, FlagConfig& f_config) {
	std::string flags;

	flags = " --area_no " + std::to_string(p_config.area_no);
	flags += " --tframe_run " + std::to_string(p_config.tframe_run);
	flags += " --thresh " + std::to_string(p_config.thresh);
	flags += " --epsilon " + std::to_string(p_config.epsilon);
	flags += " --vol_cuvette " + std::to_string(p_config.vol_cuvette);
	flags += " --is_dosage " + std::to_string(f_config.dosage);

	return flags;
}

StringSet getRelSubDirectories(fs::path& currentPath, StringList& csvFiles) {
	// creates stringlist with final sub directories
	StringSet dirs;
	for (const auto& file : csvFiles) {
		auto parent = fs::path(file).parent_path();
		auto relParent = fs::relative(parent, currentPath).string();
		dirs.insert(relParent);
	}
	return dirs;
}

std::string generatePythonCommand(std::string& main, std::string& file, std::string& flags) {
	// windows or mac/linux
	#ifdef _WIN32
		std::string pythonCmd = "python";
	#else
		std::string pythonCmd = "python3";
	#endif

	auto command = pythonCmd + " \"" + main + "\" --file \"" + file + "\" " + flags;

	return command;
}

nlohmann::json readJsonFile(fs::path& currentPath) {
	auto jsonFilePath = currentPath / "temp_result.json";
	std::ifstream jsonFile(jsonFilePath);

	if (!jsonFile.is_open()) {
		std::cerr << "Error: No temp_result.json file was generated\n";
		std::exit(1);
	}

	nlohmann::json res;
	try {
		res = nlohmann::json::parse(jsonFile);
		jsonFile.close();
	} catch (const nlohmann::json::parse_error& e) {
		std::cerr << "Error parsing the temp_result.json file\n"
				  << e.what() << "\n";
		std::exit(1);
	}

	std::remove(jsonFilePath.c_str());
	return res;
}

std::map<std::string, double> getMeanValues(std::map<std::string, std::vector<double>>& values_map) {
	std::map<std::string, double> means;
	for (auto& [name, values] : values_map) {
		double sum = 0.0;
		for (auto& value : values) sum += value;
		means[name] = sum / values.size();
	}

	return means;
}

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

	// sort found files
	sortFiles(csvFiles);

	// initiate logFile
	auto logFilePath = createLogFile(currentPath);

	// get python flags
	auto flags = generatePythonFlags(p_config, f_config);

	// get sub directories
	auto dirs = getRelSubDirectories(currentPath, csvFiles);

	std::vector<Measurement> entries;
	std::map<std::string, std::vector<double>> values;
	for (auto& file : csvFiles) {
		fs::path filePath(file);
		auto relFile = fs::relative(filePath, currentPath).string();
		auto name = baseName(removeExt(relFile));
		auto command = generatePythonCommand(main, file, flags);

		// run python
		int status = std::system(command.c_str());
		int code = WEXITSTATUS(status);
		if (code != 0) {
			std::cerr << relFile << " could not be analyzed. Continue with next file\n";
			continue;
		}

		auto res = readJsonFile(currentPath);
		auto v = res["v"].get<double>();
		entries.push_back({relFile, name, v});
		values[name].push_back(v);
	}

	// get mean value
	auto means = getMeanValues(values);
	
	std::string curName;
	for (auto& entry : entries) {
		if (!curName.empty() && entry.name != curName) {
			if (!f_config.dosage) {
				appendMean2LogFile(logFilePath, means[curName]);
			}
		}

		curName = entry.name;
		// append to logFile
		append2LogFile(logFilePath, entry, f_config, dirs);
	}
	if (!curName.empty()) {
		if (!f_config.dosage) {
			appendMean2LogFile(logFilePath, means[curName]);
		}
	}

	terminationMessage2LogFile(logFilePath);
		
	std::cout << "All analysis have been done. You can find your "
			  << "results in 'activity_log.txt' and the generated "
			  << "plots in the plots/ folder.\n";
}
