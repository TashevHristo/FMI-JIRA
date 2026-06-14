#include "FilterTasksCommand.h"
#include "System.h"
#include <print>

void FilterTasksCommand::execute(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2) {
        std::print("[Error] Usage: filter-tasks <criteria>\n");
        std::print("Criteria: ToDo | InProgress | InReview | Done | Low | Medium | High | Critical | Bug | Feature | Task | Improvement\n");
        return;
    }
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) {
        std::print("[Error] {}\n", studentResult.error());
        return;
    }

    bool found = false;
    for (Project* p : sys.getProjects()) {
        if (p->findUser(studentResult.value()->getUsername()) == nullptr) continue;
        for (Task* t : studentResult.value()->filterTasks(*p, tokens[1])) {
            std::print("- {}\n", t->getTask());
            found = true;
        }
    }
    if (!found) std::print("[System] No tasks found for criteria '{}'.\n", tokens[1]);
}

std::string FilterTasksCommand::getName() const
{
    return "filter-tasks";
}