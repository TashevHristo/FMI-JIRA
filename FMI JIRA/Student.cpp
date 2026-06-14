#include "Student.h"
#include "Project.h"
#include "Task.h"
#include "Comment.h"
#include "Date.h"
#include "TaskEnums.h"

Student::Student(std::string username, std::string password): User(username, password){}

std::string Student::getUsername() const
{
    return username;
}

Role Student::getRole() const
{
    return Role::Student;
}

void Student::viewProfile() const
{
    std::cout << std::format("Username: {}, Role: Student\n", username);
}

std::expected<Student*, std::string> Student::asStudent()
{
    return this;
}

std::expected<void, std::string> Student::joinProject(Project& project)
{
    if (project.findUser(username) != nullptr) return std::unexpected("The user is already in this project.");

    project.addUser(this);
    return {};
}

std::expected<void, std::string> Student::createTask(Project& project, std::string title, std::string description, 
    TaskType type, TaskPriority priority, Date deadline)
{
    if (project.findUser(username) == nullptr)
        return std::unexpected("You are not a member of this project.");
    Task* task = new Task(std::move(title), std::move(description), type, priority, deadline);
    project.addTask(task);
    return {};
}

std::expected<void, std::string> Student::assignTask(Project& project, const std::string& taskId)
{
    if(project.findUser(username) == nullptr) return std::unexpected("You are not a member of this project.");

    Task* task = project.findTask(taskId);
    if (task == nullptr) return std::unexpected("Task not found.");

    if (task->getUserInCharge() != nullptr) return std::unexpected("Task is already assingned to someone.");

    task->assignUser(this);
    return {};
}

std::expected<void, std::string> Student::changeStatus(Project& project, const std::string& taskId, TaskStatus status)
{
    if (project.findUser(username) == nullptr) return std::unexpected("You are not a member of this project.");

    Task* task = project.findTask(taskId);
    if (task == nullptr) return std::unexpected("Task not found.");

    if (task->getUserInCharge() == nullptr || task->getUserInCharge()->getUsername() != username)
        return std::unexpected("You are not assigned to this task.");

    task->changeStatus(status);
    return {};
}

std::expected<void, std::string> Student::addComment(Project& project, const std::string& taskId, Comment* comment)
{
    if (project.findUser(username) == nullptr)
        return std::unexpected("You are not a member of this project.");

    Task* task = project.findTask(taskId);
    if (task == nullptr)
        return std::unexpected("Task not found.");

    task->addComment(comment);
    return {};
}

std::expected<void, std::string> Student::addTag(Project& project, const std::string& taskId, const std::string& tag)
{
    if (project.findUser(username) == nullptr)
        return std::unexpected("You are not a member of this project.");

    Task* task = project.findTask(taskId);
    if (task == nullptr)
        return std::unexpected("Task not found.");

    task->addTag(tag);
    return {};
}

std::vector<Task*> Student::getMyTasks(const Project& project) const
{
    std::vector<Task*> myTasks;
    for (auto& task : project.getTasks()) {
        if (task->getUserInCharge() != nullptr &&
            task->getUserInCharge()->getUsername() == username) {
            myTasks.push_back(task);
        }
    }

    return myTasks;
}

std::vector<Task*> Student::getUpcomingTasks(const Project& project, const Date& before) const
{
    std::vector<Task*> upcomingTasks;
    for (auto& task : project.getTasks()) {
        if (task->getUserInCharge() != nullptr &&
            task->getUserInCharge()->getUsername() == username &&
            task->getStatus() != TaskStatus::Done &&
            task->getDeadline() <= before) {
            upcomingTasks.push_back(task);
        }
    }
    return upcomingTasks;
}

std::vector<Task*> Student::searchTasks(const Project& project, const std::string& keyword) const
{
    std::vector<Task*> result;
    for (Task* task : project.getTasks()) {
        if (task->getTitle().find(keyword) != std::string::npos ||
            task->getDescription().find(keyword) != std::string::npos) {
            result.push_back(task);
        }
    }
    return result;
}

std::vector<Task*> Student::filterTasks(const Project& project, const std::string& criteria) const
{
    std::vector<Task*> result;
    for (Task* task : project.getTasks()) {

        if (criteria == "ToDo" && task->getStatus() == TaskStatus::ToDo)
            result.push_back(task);
        else if (criteria == "InProgress" && task->getStatus() == TaskStatus::InProgress)
            result.push_back(task);
        else if (criteria == "InReview" && task->getStatus() == TaskStatus::InReview)
            result.push_back(task);
        else if (criteria == "Done" && task->getStatus() == TaskStatus::Done)
            result.push_back(task);

        else if (criteria == "Low" && task->getPriority() == TaskPriority::Low)
            result.push_back(task);
        else if (criteria == "Medium" && task->getPriority() == TaskPriority::Medium)
            result.push_back(task);
        else if (criteria == "High" && task->getPriority() == TaskPriority::High)
            result.push_back(task);
        else if (criteria == "Critical" && task->getPriority() == TaskPriority::Critical)
            result.push_back(task);

        else if (criteria == "Bug" && task->getType() == TaskType::Bug)
            result.push_back(task);
        else if (criteria == "Feature" && task->getType() == TaskType::Feature)
            result.push_back(task);
        else if (criteria == "Task" && task->getType() == TaskType::Task)
            result.push_back(task);
        else if (criteria == "Improvement" && task->getType() == TaskType::Improvement)
            result.push_back(task);
    }
    return result;
}
