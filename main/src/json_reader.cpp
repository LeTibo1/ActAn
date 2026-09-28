#include "json_reader.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ProgramConfig loadConfigFile(const std::string& file_path) {
	ProgramConfig config;
	std::ifstream file(file_path);

	if (!file.is_open()) {
		std::cerr << "Problem with reading the config.json file:\n"
				  << file_path << "\n"
				  << "Please contact the designer of this program\n";
		std::exit(1);
	}

	try {
		json data = json::parse(file);

		StringList requiredFields = {
			"area_no", "tframe_run", "thresh", "epsilon", "vol_cuvette",
		};

		for (const auto& field : requiredFields) {
			if (!data.contains(field)) {
				std::cerr << "Warning! One parameter is missing in the config file.\n"
						  << "If you have modified the file, please make sure that "
						  << "all parameter are present.\n"
						  << "Otherwise, please contact the designer of the program\n";
				std::exit(1);
			}
		}

		config.area_no 		= data["area_no"];
		config.tframe_run	= data["tframe_run"];
		config.thresh    	= data["thresh"];
		config.epsilon   	= data["epsilon"];
		config.vol_cuvette  = data["vol_cuvette"];
	} catch (const json::parse_error& e) {
		std::cerr << e.what() << "\n"
				  << "Please contact the designer of this program\n";
		std::exit(1);
	}

	return config;
}
