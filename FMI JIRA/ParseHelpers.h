#pragma once
#include "TaskEnums.h"
#include "Roles.h"
#include <string>
#include <stdexcept>

inline TaskType parseTaskType(const std::string& type)
{
    if (type == "Bug")         return TaskType::Bug;
    if (type == "Feature")     return TaskType::Feature;
    if (type == "Task")        return TaskType::Task;
    if (type == "Improvement") return TaskType::Improvement;
    throw std::invalid_argument("Invalid task type: " + type);
}

inline TaskPriority parseTaskPriority(const std::string& priority)
{
    if (priority == "Low")      return TaskPriority::Low;
    if (priority == "Medium")   return TaskPriority::Medium;
    if (priority == "High")     return TaskPriority::High;
    if (priority == "Critical") return TaskPriority::Critical;
    throw std::invalid_argument("Invalid priority: " + priority);
}

inline TaskStatus parseTaskStatus(const std::string& status)
{
    if (status == "ToDo")       return TaskStatus::ToDo;
    if (status == "InProgress") return TaskStatus::InProgress;
    if (status == "InReview")   return TaskStatus::InReview;
    if (status == "Done")       return TaskStatus::Done;
    throw std::invalid_argument("Invalid status: " + status);
}

inline Role parseRole(const std::string& role)
{
    if (role == "Student")           return Role::Student;
    if (role == "TeachingAssistant") return Role::TeachingAssistant;
    if (role == "Lecturer")          return Role::Lecturer;
    throw std::invalid_argument("Invalid role: " + role);
}