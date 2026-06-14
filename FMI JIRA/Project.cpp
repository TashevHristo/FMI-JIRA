#include <iostream>
#include <vector>
#include <algorithm>
#include "Project.h"
#include "ProjectStatus.h"
#include "User.h"
#include "Task.h"
#include "Stage.h"

Project::Project(std::string name, std::string description): name(std::move(name)), description(std::move(description)){}

std::expected<void, std::string> Project::finalize()
{
    if (status != ProjectStatus::Active) {
        return std::unexpected("Only active project can be finalized.");
    }
    status = ProjectStatus::Finished;
    return{};
}

std::expected<void, std::string> Project::archive()
{
    if (status != ProjectStatus::Finished) {
        return std::unexpected("Only finalized project can be archived.");
    }
    status = ProjectStatus::Archived;
    return {};
}

void Project::addUser(User* user)
{
    users.push_back(user);
}

void Project::addTask(Task* task)
{
    tasks.push_back(task);
}

void Project::addStage(Stage* stage)
{
    stages.push_back(stage);
}

std::expected<void, std::string> Project::removeUser(const std::string& username)
{
    auto removed = std::erase_if(users, [&username](const User* user) {
        return user->getUsername() == username;
        });

    if (removed == 0) {
        return std::unexpected(std::format("No user with username: {} found", username));
    }
    return {};
}

std::expected<void, std::string> Project::removeTask(std::string taskId)
{
    auto removed = std::erase_if(tasks, [&taskId](const Task* task) {
        return task->getId() == taskId;
        });

    if (removed == 0) {
        return std::unexpected(std::format("No task with id: {} found", taskId));
    }
    return {};
}

const std::string Project::getProject() const
{
    return std::format("Name: {}, Description: {}, Status: {}", name, description, toString(status));
}

const std::string Project::getName() const
{
    return name;
}

ProjectStatus Project::getStatus() const
{
    return status;
}

const std::vector<User*> Project::getUsers() const
{
    return users;
}

const std::vector<Task*> Project::getTasks() const
{
    return tasks;
}

const std::vector<Stage*> Project::getStages() const
{
    return stages;
}

User* Project::findUser(const std::string& username) const
{
    for (auto& user : users) {
        if (user->getUsername() == username) return user;
    }
    return nullptr;
}

Task* Project::findTask(const std::string& taskId) const
{
    for (auto& task : tasks) {
        if (task->getId() == taskId) return task;
    }
    return nullptr;
}

Stage* Project::findStage(const std::string& stageName) const
{
    for (auto& stage : stages) {
        if (stage->getName() == stageName) return stage;
    }
    return nullptr;
}