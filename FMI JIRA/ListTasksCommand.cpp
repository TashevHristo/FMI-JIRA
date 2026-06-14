#include "ListTasksCommand.h"
#include <iostream>
#include <print>
#include <vector>
#include "System.h"
#include "Student.h"

void ListTasksCommand::execute(const std::vector<std::string>& tokens)
{
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) { std::print("[Error] {}\n", studentResult.error()); return; }

    bool found = false;
    for (Project* project : sys.getProjects()) {
        if (project->findUser(studentResult.value()->getUsername()) == nullptr) continue;
        for (Task* t : project->getTasks()) {
            std::print("- {}\n", t->getTask());
            found = true;
        }
    }
    if (!found) std::print("[System] No tasks found.\n");
}

std::string ListTasksCommand::getName() const
{
    return "list-tasks";
}
