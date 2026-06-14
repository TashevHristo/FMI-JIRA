#include "SaveCommand.h"
#include "System.h"
#include <print>

void SaveCommand::execute(const std::vector<std::string>& tokens)
{
	System& sys = System::getInstance();

	auto adminResult = sys.getCurrentUser()->asProjectManager();
	if (!adminResult) {
		std::print("[Error] {}\n", adminResult.error());
		return;
	}

	auto result = sys.save();
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
	std::print("[System] Data saved successfully.\n");
}

std::string SaveCommand::getName() const
{
	return "save";
}
