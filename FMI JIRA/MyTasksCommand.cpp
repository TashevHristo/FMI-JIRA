#include "MyTasksCommand.h"
#include "System.h"
#include <print>

void MyTasksCommand::execute(const std::vector<std::string>& tokens)
{
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) { std::print("[Error] {}\n", studentResult.error()); return; }

    int completed = 0, inProgress = 0, score = 0;
    for (Project* p : sys.getProjects()) {
        for (Task* t : studentResult.value()->getMyTasks(*p)) {
            if (t->getStatus() == TaskStatus::Done) { completed++; score += 10; }
            else if (t->getStatus() == TaskStatus::InProgress) inProgress++;
        }
    }
    std::print("Completed tasks: {}\nIn progress: {}\nPerformance score: {}\n",
        completed, inProgress, score);
}

std::string MyTasksCommand::getName() const
{
    return "my-tasks";
}
