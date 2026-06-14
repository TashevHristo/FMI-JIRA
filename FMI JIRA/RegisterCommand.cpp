#include "RegisterCommand.h"
#include "System.h"
#include "ParseHelpers.h"
#include <print>

void RegisterCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 4) {
		std::print("[Error] Usage: register <username> <password> <role>\n");
		return;
	}
	System& sys = System::getInstance();

	auto adminResult = sys.getCurrentUser()->asProjectManager();
	if (!adminResult) {
		std::print("[Error] {}\n", adminResult.error());
		return;
	}

	try {
		Role role = parseRole(tokens[3]);
		auto result = sys.registerUser(tokens[1], tokens[2], role);
		if (!result) {
			std::print("[Error] {}\n", result.error());
			return;
		}
		std::print("[System] User '{}' registered.\n", tokens[1]);
	}
	catch (const std::invalid_argument& e) {
		std::print("[Error] {}\n", e.what());
	}
}

std::string RegisterCommand::getName() const
{
	return "register";
}
