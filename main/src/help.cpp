#include "help.h"
#include <iostream>

ParseAction printHelp() {
	auto message = {
		"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=",
		"=-= Faciliate the analysis of the activity measurements =-=",
		"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=",
		"Usage: actan [OPTIONS]",
		"",
		"OPTIONS:",
		"  Analysis Parameters:",
		"    --area_no <NUMBER>        number of area that is analysed",
		"                              default: 3 (mostly the last area)",
		"",
		"    --tframe_run <SECONDS>    time frame (s) of the analysed area",
		"                              default: 60 (s)",
		"",
		"  Laboratory & Physical Paramters:",
		"    --epsilon [double]        extinction coefficient of absorbant",
		"                              default: 0.00622 (NADPH)",
		"",
		"    --vol_cuvette [double]    volume of solution (mL) in the cuvette",
		"                              default: 1.2 (mL)",
		"",
		"  Sensitive Settings:",
		"    --thresh [double]         threshold of area_picker",
		"                              default: 0.05",
		"      CAUTION: Changing this parameter can lead to wrong values.",
		"               Only change this if you know what you are doing",
		"",
		"  General:",
		"    -h, --help                show this help message",
		"",
		"Example:  actan --area_no 2 --vol_cuvette 1.0",
		"",
		"Permanent Configuration:",
		"  To change theses parameters permanently, open and modify",
		"  the configuration file:",
		"  ->  /actan/config/config.json",
		"",
		"  CAUTION: Incorrectly modifying this file may cause the",
		"           program to stop working.",
		"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=",
	};

	for (const auto& msg : message) {
		std::cout << msg << "\n";
	}
	return ParseAction::Return;
}
