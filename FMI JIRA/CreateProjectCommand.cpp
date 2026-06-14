#include "CreateProjectCommand.h"
#include "System.h"
#include <print>

void CreateProjectCommand::execute(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2) {
        std::print("[Error] Usage: create-project <name>\n");
        return;
    }
    System& sys = System::getInstance();

    auto adminResult = sys.getCurrentUser()->asProjectManager();
    if (!adminResult) { 
        std::print("[Error] {}\n", adminResult.error()); 
        return; 
    }

    auto result = adminResult.value()->createProject(sys.getProjects(), tokens[1]);
    if (!result) { std::print("[Error] {}\n", result.error()); return; }
    std::print("[System] Project '{}' created successfully.\n", tokens[1]);
}

std::string CreateProjectCommand::getName() const
{
    return "create-project";
}
