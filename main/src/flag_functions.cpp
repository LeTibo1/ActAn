#include "flag_functions.h"
#include <unordered_map>
#include <iostream>

void setConfigValue(const std::string& key, const std::string& valueAsString, ProgramConfig& config) {
	// int values
	std::unordered_map<std::string, int*> intFields = {
		{"area_no", &config.area_no},
		{"tframe_run", &config.tframe_run},
	};

	// double values
	std::unordered_map<std::string, double*> doubleFields = {
		{"thresh", &config.thresh},
		{"epsilon", &config.epsilon},
		{"vol_cuvette", &config.vol_cuvette},
	};

	auto intIt = intFields.find(key);
	if (intIt != intFields.end()) {
		*intIt->second = std::stoi(valueAsString);
		std::cout << "Changed setting for '" << key << "' to " << valueAsString << "\n";
		return;
	}

	auto doubleIt = doubleFields.find(key);
	if (doubleIt != doubleFields.end()) {
		*doubleIt->second = std::stod(valueAsString);
		std::cout << "Changed setting for '" << key << "' to " << valueAsString << "\n";
		return;
	}

	std::cerr << "Warning: key '" << key << "' does not exist in the config\n";
}
