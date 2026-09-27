#include "dispatcher.h"
#include "help.h"
#include <iostream>
#include <unordered_map>
#include <functional>


ParseAction dispatch(const StringList& args) {
	std::unordered_map<std::string, std::function<ParseAction()>> actions = {
		{"--help", printHelp},
		{"-h", printHelp},
	};

	for (const auto& arg : args) {
		auto it = actions.find(arg);

		if (it != actions.end()) {
			auto action = it->second();
			if (action == ParseAction::Return) {
				return ParseAction::Return;
			}
			if (action == ParseAction::Continue) {
				continue;
			}
		} else {
			std::cout << "Unknown command: " << arg << "\n";
			return ParseAction::Error;
		}
	}
	
	return ParseAction::Continue;
}
