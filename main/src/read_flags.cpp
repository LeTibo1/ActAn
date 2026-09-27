#include "read_flags.h"


ParseAction parseFlag(const std::function<ParseAction()>& targetFunction) {
	return targetFunction();
}

ParseAction parseSingleInput(
		const StringList& args, size_t& index,
		const std::function<ParseAction(const std::string&)>& targetFunction
) {
	if (
		index + 1 < args.size() &&
		!args.at(index + 1).empty() &&
		args.at(index + 1).at(0) != '-'
	) {
		index++;
		return targetFunction(args.at(index));
	}
	std::cerr << "Error: " << args.at(index) << " needs a value\n";
	return ParseAction::Error;
}

ParseAction parseMultipleInputs(
	const StringList& args, size_t& index,
	const std::function<ParseAction(const StringList&)>& targetFunction
) {
	StringList values;
	while (
		index + 1 < args.size() &&
		!args.at(index + 1).empty() &&
		args.at(index + 1).at(0) != '-'
	) {
		index++;
		values.push_back(args.at(index));
	}

	if (values.size() != 0) {
		return targetFunction(values);
	}

	std::cerr << "Error: " << args.at(index) << " needs multiple values\n";
	return ParseAction::Error;
}
