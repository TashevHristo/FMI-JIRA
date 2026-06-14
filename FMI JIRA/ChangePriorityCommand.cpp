#include "ChangePriorityCommand.h"
#include "System.h"
#include "ParseHelpers.h"
#include <print>

void ChangePriorityCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 3) {
		std::print("[Error] Usage: change-priority <task_id> <priority>\n");
		return;
	}
	System& sys = System::getInstance();

	auto approverResult = sys.getCurrentUser()->asTaskApprover();
	if (!approverResult) {
		std::print("[Error] {}\n", approverResult.error());
		return;
	}

	Project* project = sys.findProjectByTask(tokens[1]);
	if (!project) {
		std::print("[Error] Task '{}' not found.\n", tokens[1]);
		return;
	}

	Task* task = project->findTask(tokens[1]);
	try {
		TaskPriority priority = parseTaskPriority(tokens[2]);
		task->changePriority(priority);
		std::print("[System] Priority changed successfully.\n");
	}
	catch (const std::invalid_argument& e) {
		std::print("[Error] {}\n", e.what());
	}
}

std::string ChangePriorityCommand::getName() const
{
	return "change-priority";
}
