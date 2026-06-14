#include "SearchTasksCommand.h"
#include "System.h"
#include <print>

void SearchTasksCommand::execute(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2) {
        std::print("[Error] Usage: search-tasks <keyword>\n");
        return;
    }
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) {
        std::print("[Error] {}\n", studentResult.error());
        return;
    }

    bool found = false;
    for (Project* project : sys.getProjects()) {
        if (project->findUser(studentResult.value()->getUsername()) == nullptr) continue;
        for (Task* t : studentResult.value()->searchTasks(*project, tokens[1])) {
            std::print("- {}\n", t->getTask());
            found = true;
        }
    }
    if (!found) std::print("[System] No tasks found matching '{}'.\n", tokens[1]);
}

std::string SearchTasksCommand::getName() const
{
    return "search-tasks";
}