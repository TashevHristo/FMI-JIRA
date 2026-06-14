#include "TeachingAssistant.h"
#include <iostream>
#include "Project.h"
#include "Task.h"
#include "Stage.h"
#include "TaskEnums.h"
#include "StageStatus.h"

TeachingAssistant::TeachingAssistant(std::string username, std::string password): User(std::move(username), std::move(password)) {}

std::string TeachingAssistant::getUsername() const
{
    return username;
}

Role TeachingAssistant::getRole() const
{
    return Role::TeachingAssistant;
}

void TeachingAssistant::viewProfile() const
{
    std::cout << std::format("Username: {}, Role: Teaching Assistant\n", username);
}

std::expected<ITaskApprover*, std::string> TeachingAssistant::asTaskApprover()
{
    return this;
}

std::expected<IStageManager*, std::string> TeachingAssistant::asStageManager()
{
    return this;
}

std::expected<void, std::string> TeachingAssistant::approveTask(Project& project, const std::string& taskId)
{
    Task* task = project.findTask(taskId);
    if (task == nullptr)
        return std::unexpected(std::format("Task {} not found.", taskId));

    if (task->getStatus() != TaskStatus::InReview)
        return std::unexpected("Only tasks in review can be approved.");

    task->changeStatus(TaskStatus::Done);
    return {};
}

std::expected<void, std::string> TeachingAssistant::reviewTask(Project& project, const std::string& taskId)
{
    Task* task = project.findTask(taskId);
    if (task == nullptr)
        return std::unexpected(std::format("Task {} not found.", taskId));

    if (task->getStatus() != TaskStatus::InProgress)
        return std::unexpected("Only tasks in progress can be reviewed.");

    task->changeStatus(TaskStatus::InReview);
    return {};
}

std::expected<void, std::string> TeachingAssistant::startStage(Project& project, const std::string& name)
{
    Stage* stage = project.findStage(name);
    if (stage == nullptr)
        return std::unexpected(std::format("Stage '{}' not found.", name));

    stage->startStage();
    return {};
}

std::expected<void, std::string> TeachingAssistant::endStage(Project& project, const std::string& name)
{
    Stage* stage = project.findStage(name);
    if (stage == nullptr)
        return std::unexpected(std::format("Stage '{}' not found.", name));

    stage->finishStage();
    return {};
}

std::expected<void, std::string> TeachingAssistant::moveTaskToStage(Project& project, const std::string& taskId, const std::string& name)
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

std::expected<void, std::string> TeachingAssistant::stageReport(Project& project, const std::string& name)
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