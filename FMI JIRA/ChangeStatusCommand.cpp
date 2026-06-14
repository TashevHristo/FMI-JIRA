#include "ChangeStatusCommand.h"
#include "System.h"
#include "ParseHelpers.h"
#include <print>

void ChangeStatusCommand::execute(const std::vector<std::string>& tokens)
{
    if(tokens.size() < 3) {
        std::print("[Error] Usage: change-status <task_id> <status>\n");
        return;
    }
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) { std::print("[Error] {}\n", studentResult.error()); return; }

    Project* project = sys.findProjectByTask(tokens[1]);
    if (!project) { std::print("[Error] Task '{}' not found.\n", tokens[1]); return; }

    try {
        TaskStatus status = parseTaskStatus(tokens[2]);
        auto result = studentResult.value()->changeStatus(*project, tokens[1], status);
        if (!result) { std::print("[Error] {}\n", result.error()); return; }
        std::print("[System] Status updated successfully.\n");
    }
    catch (const std::invalid_argument& e) {
        std::print("[Error] {}\n", e.what());
    }
}

std::string ChangeStatusCommand::getName() const
{
    return "change-status";
}
