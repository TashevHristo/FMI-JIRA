#include "ListAllTasksCommand.h"
#include "System.h"
#include <print>

void ListAllTasksCommand::execute(const std::vector<std::string>& tokens)
{
	System& sys = System::getInstance();

	auto lecturerResult = sys.getCurrentUser()->asLecturer();
	if (!lecturerResult) {
		std::print("[Error] {}\n", lecturerResult.error());
		return;
	}

	bool found = false;
	for (Project* p : sys.getProjects()) {
		for (Task* t : p->getTasks()) {
			std::print("- {}\n", t->getTask());
			found = true;
		}
	}
	if (!found) std::print("[System] No tasks found.\n");
}

std::string ListAllTasksCommand::getName() const
{
	return "list-all-tasks";
}
