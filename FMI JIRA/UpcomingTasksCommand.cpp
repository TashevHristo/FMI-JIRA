#include "UpcomingTasksCommand.h"
#include "System.h"
#include <print>

void UpcomingTasksCommand::execute(const std::vector<std::string>& tokens)
{
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) { std::print("[Error] {}\n", studentResult.error()); return; }

    Date nextWeek = Date::addDays(Date::today(), 7);

    bool found = false;
    for (Project* p : sys.getProjects()) {
        for (Task* t : studentResult.value()->getUpcomingTasks(*p, nextWeek)) {
            std::print("- {} | Deadline: {}\n", t->getTask(), t->getDeadline().getDate());
            found = true;
        }
    }
    if (!found) std::print("[System] No upcoming tasks.\n");
}

std::string UpcomingTasksCommand::getName() const
{
    return "upcoming-tasks";
}
