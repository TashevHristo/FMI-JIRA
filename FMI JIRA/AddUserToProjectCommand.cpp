#include "AddUserToProjectCommand.h"
#include "System.h"
#include <print>

void AddUserToProjectCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 3) {
		std::print("[Error] Usage: add-user-to-project <user> <project>\n");
		return;
	}
	System& sys = System::getInstance();

	auto adminResult = sys.getCurrentUser()->asProjectManager();
	if (!adminResult) {
		std::print("[Error] {}\n", adminResult.error());
		return;
	}

	auto result = adminResult.value()->addUser(sys.getProjects(), sys.getUsers(), tokens[1], tokens[2]);
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
	std::print("[System] {} added to project {}.\n", tokens[1], tokens[2]);
}

std::string AddUserToProjectCommand::getName() const
{
	return "add-user-to-project";
}
