#include "ListProjectsCommand.h"
#include <iostream>
#include <print>
#include <vector>
#include "System.h"
#include "Student.h"

void ListProjectsCommand::execute(const std::vector<std::string>& tokens)
{
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) { std::print("[Error] {}\n", studentResult.error()); return; }

    bool found = false;
    for (Project* project : sys.getProjects()) {
        if (project->findUser(studentResult.value()->getUsername()) != nullptr) {
            std::print("- {}\n", project->getName());
            found = true;
        }
    }
    if (!found) std::print("[System] You are not a member of any project.\n");
}

std::string ListProjectsCommand::getName() const
{
    return "list-projects";
}