#include "dispatcher.h"
#include "help.h"
#include "read_flags.h"
#include <iostream>
#include <unordered_map>
#include <functional>

void dispatch(const StringList& args) {
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
