#include "ListAllProjectsCommand.h"
#include "System.h"
#include <print>

void ListAllProjectsCommand::execute(const std::vector<std::string>& tokens)
{
	System& sys = System::getInstance();

	auto lecturerResult = sys.getCurrentUser()->asLecturer();
	if (!lecturerResult) {
		std::print("[Error] {}\n", lecturerResult.error());
		return;
	}

	bool found = false;
	for (Project* p : sys.getProjects()) {
		std::print("- {}\n", p->getName());
		found = true;
	}
	if (!found) std::print("[System] No projects found.\n");
}

std::string ListAllProjectsCommand::getName() const
{
	return "list-all-projects";
}
