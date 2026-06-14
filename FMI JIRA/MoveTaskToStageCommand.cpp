#include "MoveTaskToStageCommand.h"
#include "System.h"
#include <print>

void MoveTaskToStageCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 3) {
		std::print("[Error] Usage: move-task-to-stage <task_id> <stage_name>\n");
		return;
	}
	System& sys = System::getInstance();

	auto managerResult = sys.getCurrentUser()->asStageManager();
	if (!managerResult) {
		std::print("[Error] {}\n", managerResult.error());
		return;
	}

	Project* project = sys.findProjectByTask(tokens[1]);
	if (!project) {
		std::print("[Error] Task '{}' not found.\n", tokens[1]);
		return;
	}

	auto result = managerResult.value()->moveTaskToStage(*project, tokens[1], tokens[2]);
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
	std::print("[System] Task '{}' moved to stage '{}'.\n", tokens[1], tokens[2]);
}

std::string MoveTaskToStageCommand::getName() const
{
	return "move-task-to-stage";
}
