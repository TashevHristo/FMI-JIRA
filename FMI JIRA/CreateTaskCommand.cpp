#include "CreateTaskCommand.h"
#include "System.h"
#include "ParseHelpers.h"
#include <print>

void CreateTaskCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 4) {
		std::print("[Error] Usage: create-task <project> <type> <priority>\n");
		return;
	}
	System& sys = System::getInstance();

	auto studentResult = sys.getCurrentUser()->asStudent();
	if (!studentResult) {
		std::print("[Error] {}\n", studentResult.error());
		return;
	}

	Project* project = sys.findProject(tokens[1]);
	if (!project) {
		std::print("[Error] Project '{}' not found.\n", tokens[1]);
		return;
	}

	try {
		TaskType type = parseTaskType(tokens[2]);
		TaskPriority priority = parseTaskPriority(tokens[3]);

		std::string title, description, deadlineStr;
		std::print("Title: ");
		std::getline(std::cin, title);
		std::print("Description: ");
		std::getline(std::cin, description);
		std::print("Deadline (dd/mm/yyyy): ");
		std::cin >> deadlineStr;
		std::cin.ignore();

		Date deadline = Date::parse(deadlineStr);
		auto result = studentResult.value()->createTask(*project, title, description, type, priority, deadline);
		if (!result) { std::print("[Error] {}\n", result.error()); return; }

		auto& tasks = project->getTasks();
		std::print("[System] Task {} created successfully.\n", tasks.back()->getId());
	}
	catch (const std::invalid_argument& e) {
		std::print("[Error] {}\n", e.what());
	}
}

std::string CreateTaskCommand::getName() const
{
	return "create-task";
}
