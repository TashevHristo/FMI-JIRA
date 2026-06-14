#include "AddTagCommand.h"
#include "System.h"
#include <print>

void AddTagCommand::execute(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 3) {
        std::print("[Error] Usage: add-tag <task_id> <tag>\n");
        return;
    }
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) { std::print("[Error] {}\n", studentResult.error()); return; }

    Project* project = sys.findProjectByTask(tokens[1]);
    if (!project) { std::print("[Error] Task '{}' not found.\n", tokens[1]); return; }

    auto result = studentResult.value()->addTag(*project, tokens[1], tokens[2]);
    if (!result) { std::print("[Error] {}\n", result.error()); return; }
    std::print("[System] Tag added.\n");
}

std::string AddTagCommand::getName() const
{
    return "add-tag";
}
