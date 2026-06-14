#include "RemoveUserCommand.h"
#include "System.h"
#include <print>

void RemoveUserCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 2) {
		std::print("[Error] Usage: remove-user <user>\n");
		return;
	}
	System& sys = System::getInstance();

	auto adminResult = sys.getCurrentUser()->asProjectManager();
	if (!adminResult) {
		std::print("[Error] {}\n", adminResult.error());
		return;
	}

	if (tokens[1] == sys.getCurrentUser()->getUsername()) {
		std::print("[Error] Cannot remove the Administrator.\n");
		return;
	}

	auto result = adminResult.value()->removeUser(sys.getProjects(), sys.getUsers(), tokens[1]);
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
	std::print("[System] User '{}' removed successfully.\n", tokens[1]);
}

std::string RemoveUserCommand::getName() const
{
	return "remove-user";
}
