#include "dispatcher.h"
#include "help.h"
#include "read_flags.h"
#include <iostream>
#include <unordered_map>
#include <functional>

ParseAction dispatch(const StringList& args) {
	// map of all available flags
	std::unordered_map<std::string, std::function<ParseAction(const StringList&, size_t&)>> actions = {
		{"--help", [](const StringList&, size_t&) { return parseFlag(printHelp); }},
		{"-h", [](const StringList&, size_t&) { return parseFlag(printHelp); }},
	};

	// evaluating args and finding right flag parser
	for (size_t i = 0; i < args.size(); i++) {
		const auto& arg = args.at(i);
		auto it = actions.find(arg);

		if (it != actions.end()) {
			auto action = it->second(args, i);

			if (action == ParseAction::Return) {
				return ParseAction::Return;
			} else if (action == ParseAction::Error) {
				return ParseAction::Error;
			} else if (action == ParseAction::Continue) {
				continue;
			}
		} else {
			std::cout << "Unknown command: " << arg << "\n";
			return ParseAction::Error;
		}
	}
	
	return ParseAction::Continue;
}
