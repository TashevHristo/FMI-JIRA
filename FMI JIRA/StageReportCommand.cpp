#include "StageReportCommand.h"
#include "System.h"
#include <print>

void StageReportCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 2) {
		std::print("[Error] Usage: stage-report <stage_name>\n");
		return;
	}
	System& sys = System::getInstance();

	auto managerResult = sys.getCurrentUser()->asStageManager();
	if (!managerResult) {
		std::print("[Error] {}\n", managerResult.error());
		return;
	}

	Project* project = sys.findProjectByStage(tokens[1]);
	if (!project) {
		std::print("[Error] Stage '{}' not found.\n", tokens[1]);
		return;
	}

	auto result = managerResult.value()->stageReport(*project, tokens[1]);
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
}

std::string StageReportCommand::getName() const
{
	return "stage-report";
}
