#pragma once
#include "actions.h"
#include "types.h"
#include <functional>

ParseAction parseFlag(const std::function<ParseAction()>& targetFunction);
ParseAction parseSingleInput(
	const StringList& args, size_t& index,
	const std::function<ParseAction(const std::string&)>& targetFunction
);
ParseAction parseMultipleInputs(
	const StringList& args, size_t& index,
	const std::function<ParseAction(const StringList&)>& targetFunction
);
