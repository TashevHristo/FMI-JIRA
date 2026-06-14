#include "LoadCommand.h"
#include "System.h"
#include <print>

void LoadCommand::execute(const std::vector<std::string>& tokens)
{
	System& sys = System::getInstance();

	auto adminResult = sys.getCurrentUser()->asProjectManager();
	if (!adminResult) {
		std::print("[Error] {}\n", adminResult.error());
		return;
	}

	auto result = sys.load();
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
	std::print("[System] Data loaded successfully.\n");
}

std::string LoadCommand::getName() const
{
	return "load";
}
