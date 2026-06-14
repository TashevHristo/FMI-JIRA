#include "Lecturer.h"
#include "Project.h"
#include "Task.h"
#include "Stage.h"
#include "TaskEnums.h"
#include "StageStatus.h"

Lecturer::Lecturer(std::string username, std::string password): User(std::move(username), std::move(password)){}

std::string Lecturer::getUsername() const
{
    return username;
}

Role Lecturer::getRole() const
{
    return Role::Lecturer;
}

void Lecturer::viewProfile() const
{
    std::cout << std::format("Username: {}, Role: Lecturer\n", username);
}

std::expected<void, std::string> Lecturer::approveTask(Project& project, const std::string& taskId)
{
    Task* task = project.findTask(taskId);
    if (task == nullptr)
        return std::unexpected(std::format("Task {} not found.", taskId));

    if (task->getStatus() != TaskStatus::InReview)
        return std::unexpected("Only tasks in review can be approved.");

    task->changeStatus(TaskStatus::Done);
    return {};
}

std::expected<void, std::string> Lecturer::reviewTask(Project& project, const std::string& taskId)
{
    Task* task = project.findTask(taskId);
    if (task == nullptr)
        return std::unexpected(std::format("Task {} not found.", taskId));

    if (task->getStatus() != TaskStatus::InProgress)
        return std::unexpected("Only tasks in progress can be reviewed.");

    task->changeStatus(TaskStatus::InReview);
    return {};
}

std::expected<void, std::string> Lecturer::startStage(Project& project, const std::string& name)
{
    Stage* stage = project.findStage(name);
    if (stage == nullptr)
        return std::unexpected(std::format("Stage '{}' not found.", name));

    stage->startStage();
    return {};
}

std::expected<void, std::string> Lecturer::endStage(Project& project, const std::string& name)
{
    Stage* stage = project.findStage(name);
    if (stage == nullptr)
        return std::unexpected(std::format("Stage '{}' not found.", name));

    stage->finishStage();
    return {};
}

std::expected<void, std::string> Lecturer::moveTaskToStage(Project& project, const std::string& taskId, const std::string& name)
{
    Task* task = project.findTask(taskId);
    if (task == nullptr)
        return std::unexpected(std::format("Task {} not found.", taskId));

    Stage* stage = project.findStage(name);
    if (stage == nullptr)
        return std::unexpected(std::format("Stage '{}' not found.", name));

    if (stage->getStatus() != StageStatus::Active)
        return std::unexpected("Can only move tasks to an active stage.");

    stage->addTask(task);
    return {};
}

std::expected<void, std::string> Lecturer::stageReport(Project& project, const std::string& name)
{
    Stage* stage = project.findStage(name);
    if (stage == nullptr)
        return std::unexpected(std::format("Stage '{}' not found.", name));

    int total = stage->getTasks().size();
    int done = 0;
    for (auto& task : stage->getTasks()) {
        if (task->getStatus() == TaskStatus::Done) done++;
    }

    std::cout << std::format("Stage: {}\nTasks: {}\nCompleted: {}\n",
        stage->getName(), total, done);
    return {};
}

std::expected<void, std::string> Lecturer::gradeTask(Project& project, const std::string& taskId, double grade)
{
    Task* task = project.findTask(taskId);
    if (task == nullptr)
        return std::unexpected(std::format("Task {} not found.", taskId));

    if (task->getStatus() != TaskStatus::Done)
        return std::unexpected("Only completed tasks can be graded.");

    task->setGrade(grade);
    return {};
}

std::expected<void, std::string> Lecturer::finalizeProject(Project& project)
{
    for (Task* task : project.getTasks()) {
        if (task->getStatus() != TaskStatus::Done)
            return std::unexpected("All tasks must be completed before finalizing.");
    }

    project.finalize();
    return {};
}

void Lecturer::studentReport(const Project& project, const std::string& username) const
{
    int completed = 0;
    double totalGrade = 0.0;
    int graded = 0;
    int totalScore = 0;

    for (Task* task : project.getTasks()) {
        if (task->getUserInCharge() == nullptr || task->getUserInCharge()->getUsername() != username) continue;

        if (task->getStatus() == TaskStatus::Done) {
            completed++;
            totalScore += 10;
            if (task->getGrade() > 0.0) {
                totalGrade += task->getGrade();
                graded++;
            }
        }
    }

    double avgGrade = graded > 0 ? (totalGrade / graded) : 0.0;
    std::cout << std::format("Completed tasks: {}\nAverage grade: {:.1f}\nPerformance score: {}\n",
        completed, avgGrade, totalScore);
}

std::expected<ITaskApprover*, std::string> Lecturer::asTaskApprover()
{
    return this;
}

std::expected<IStageManager*, std::string> Lecturer::asStageManager()
{
    return this;
}

std::expected<Lecturer*, std::string> Lecturer::asLecturer()
{
    return this;
}
