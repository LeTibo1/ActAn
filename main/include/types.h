#pragma once
#include <string>
#include <vector>
#include <unordered_set>

using StringList = std::vector<std::string>;
using StringSet = std::unordered_set<std::string>;

struct ProgramConfig {
	int area_no;
	int tframe_run;
	double thresh;
	double min_height;
	double epsilon;
	double vol_cuvette;
};

struct FlagConfig {
	bool dosage = false;
};

struct Measurement {
	std::string file, name;
	double value;
};
