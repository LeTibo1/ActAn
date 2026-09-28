#pragma once
#include <string>
#include <vector>

using StringList = std::vector<std::string>;

struct ProgramConfig {
	int area_no;
	int tframe_run;
	double thresh;
	double epsilon;
	double vol_cuvette;
};
