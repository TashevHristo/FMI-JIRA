#include "StudentReportCommand.h"
#include "System.h"
#include <print>

void StudentReportCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 2) {
		std::print("[Error] Usage: student-report <username>\n");
		return;
	}
	System& sys = System::getInstance();

	auto lecturerResult = sys.getCurrentUser()->asLecturer();
	if (!lecturerResult) {
		std::print("[Error] {}\n", lecturerResult.error());
		return;
	}

	User* user = sys.findUser(tokens[1]);
	if (!user) {
		std::print("[Error] User '{}' not found.\n", tokens[1]);
		return;
	}

	for (Project* p : sys.getProjects()) {
		lecturerResult.value()->studentReport(*p, tokens[1]);
	}
}

std::string StudentReportCommand::getName() const
{
	return "student-report";
}
