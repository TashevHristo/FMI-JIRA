#include "GradeTaskCommand.h"
#include "System.h"
#include <print>

void GradeTaskCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 3) {
		std::print("[Error] Usage: grade-task <task_id> <grade>\n");
		return;
	}
	System& sys = System::getInstance();

	auto lecturerResult = sys.getCurrentUser()->asLecturer();
	if (!lecturerResult) {
		std::print("[Error] {}\n", lecturerResult.error());
		return;
	}

	Project* project = sys.findProjectByTask(tokens[1]);
	if (!project) {
		std::print("[Error] Task '{}' not found.\n", tokens[1]);
		return;
	}

	try {
		double grade = std::stod(tokens[2]);
		auto result = lecturerResult.value()->gradeTask(*project, tokens[1], grade);
		if (!result) {
			std::print("[Error] {}\n", result.error());
			return;
		}
		std::print("[System] Task graded successfully.\n");
	}
	catch (const std::invalid_argument& e) {
		std::print("[Error] Invalid grade format.\n");
	}
}

std::string GradeTaskCommand::getName() const
{
	return "grade-task";
}
