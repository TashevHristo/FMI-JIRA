#include "FinalizeProjectCommand.h"
#include "System.h"
#include <print>

void FinalizeProjectCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 2) {
		std::print("[Error] Usage: finalize-project <project_name>\n");
		return;
	}
	System& sys = System::getInstance();

	auto lecturerResult = sys.getCurrentUser()->asLecturer();
	if (!lecturerResult) {
		std::print("[Error] {}\n", lecturerResult.error());
		return;
	}

	Project* project = sys.findProject(tokens[1]);
	if (!project) {
		std::print("[Error] Project '{}' not found.\n", tokens[1]);
		return;
	}

	auto result = lecturerResult.value()->finalizeProject(*project);
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
	std::print("[System] Project '{}' marked as Finished.\n", tokens[1]);
}

std::string FinalizeProjectCommand::getName() const
{
	return "finalize-project";
}
