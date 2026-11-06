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
		"    --dosage                  check if dosage of probe is in the",
		"                              right are between 54 and 64",
		"",
		"  Analysis Parameters:",
		"    --area_no <NUMBER>        number of area that is analysed",
		"                              default: 3 (mostly the last area)",
		"",
		"    --tframe_run <SECONDS>    time frame (s) of the analysed area",
		"                              default: 60 (s)",
		"",
		"  Laboratory & Physical Paramters:",
		"    --epsilon <NUMBER>        extinction coefficient of absorbant",
		"                              default: 0.00622 (NADPH)",
		"",
		"    --vol_cuvette <NUMBER>    volume of solution (mL) in the cuvette",
		"                              default: 1.2 (mL)",
		"",
		"  Sensitive Settings for area_picker:",
		"    --thresh <NUMBER>         threshold of graph changement",
		"                              default: 0.05",
		"    --min_height <NUMBER>     min height of graph increase for new area",
		"                              default: 0.7",
		"    CAUTION: Changing these parameters can lead to wrong values.",
		"             If the fitting range was selected incorrectly, adjust both",
		"             parameters to tune the sensitivity of the range detection.",
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
