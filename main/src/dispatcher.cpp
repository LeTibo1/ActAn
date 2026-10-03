#include "dispatcher.h"
#include "flag_functions.h"
#include "help.h"
#include "read_flags.h"
#include <iostream>
#include <unordered_map>
#include <functional>

void dispatch(const StringList& args, ProgramConfig& p_config, FlagConfig& f_config) {
	// map of all available flags
	std::unordered_map<std::string, std::function<ParseAction(const StringList&, size_t&)>> actions = {
		{"--help", [](const StringList&, size_t&) { return parseFlag(printHelp); }},
		{"-h", [](const StringList&, size_t&) { return parseFlag(printHelp); }},
	};

	actions["--dosage"] = [&f_config](const StringList&, size_t&) {
		auto targetFunc = [&f_config]() -> ParseAction {
			setDosageMeasure(f_config);
			return ParseAction::Continue;
		};
		return parseFlag(targetFunc);
	};

	StringList configList = {
		"area_no", "tframe_run", "thresh", "epsilon", "vol_cuvette"
	};

	for (const auto& item : configList) {
		actions["--" + item] = [item, &p_config](const StringList& a, size_t& i) {
			auto targetFunc = [item, &p_config](const std::string& valueStr) -> ParseAction {
				setConfigValue(item, valueStr, p_config);
				return ParseAction::Continue;
			};
			return parseSingleInput(a, i, targetFunc);
		};
	}

	// evaluating args and finding right flag parser
	for (size_t i = 0; i < args.size(); i++) {
		const auto& arg = args.at(i);
		auto it = actions.find(arg);

		if (it != actions.end()) {
			auto action = it->second(args, i);

			if (action == ParseAction::Return) {
				std::exit(0);
			} else if (action == ParseAction::Error) {
				std::exit(1);
			} else if (action == ParseAction::Continue) {
				continue;
			}
		} else {
			std::cout << "Unknown command: " << arg << "\n";
			std::exit(1);
		}
	}
}
