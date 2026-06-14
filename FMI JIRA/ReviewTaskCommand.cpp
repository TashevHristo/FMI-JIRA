#include "ReviewTaskCommand.h"
#include "System.h"
#include <print>

void ReviewTaskCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 2) {
		std::print("[Error] Usage: review-task <task_id>\n");
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

	auto result = approverResult.value()->reviewTask(*project, tokens[1]);
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
	std::print("[System] Task reviewed.\n");
}

std::string ReviewTaskCommand::getName() const
{
	return "review-task";
}
