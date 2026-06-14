#include "JoinProjectCommand.h"
#include <iostream>
#include <print>
#include <vector>
#include "System.h"
#include "Student.h"

void JoinProjectCommand::execute(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2) {
        std::print("[Error] Usage: join-project <project_name>\n");
        return;
    }
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) { std::print("[Error] {}\n", studentResult.error()); return; }

    Project* project = sys.findProject(tokens[1]);
    if (!project) { std::print("[Error] Project '{}' not found.\n", tokens[1]); return; }

    auto result = studentResult.value()->joinProject(*project);
    if (!result) { std::print("[Error] {}\n", result.error()); return; }
    std::print("[System] Joined project '{}'.\n", tokens[1]);
}

std::string JoinProjectCommand::getName() const
{
    return "join-project";
}
