#pragma once
#include <iostream>
#include <vector>
#include "TaskEnums.h"
#include "User.h"
#include "Date.h"

class Comment;

class Task {
	std::string id;
	std::string title;
	std::string description;
	TaskType type;
	TaskPriority priority;
	TaskStatus status = TaskStatus::ToDo;
	User* userInCharge = nullptr;
	double points = 0.0;
	double grade = 0.0;
	Date deadline;
    std::vector<Comment*> comments;
    std::vector<std::string> history;
    std::vector<std::string> tags;
public:
    static size_t id_generator;
	Task(std::string title, std::string description, TaskType type, TaskPriority priority, Date deadline);

    std::string getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    TaskType getType() const;
    TaskPriority getPriority() const;
    TaskStatus getStatus() const;
    User* getUserInCharge() const;
    double getPoints() const;
    double getGrade() const;
    const std::vector<Comment*>& getComments() const;
    const Date& getDeadline() const;
    const std::vector<std::string>& getTags() const;
    const std::vector<std::string>& getHistory() const;

    std::expected<void, std::string> changeStatus(TaskStatus newStatus);
    void changePriority(TaskPriority newPriority);
    void assignUser(User* user);
    std::expected<void, std::string> setGrade(double grade);
    void addComment(Comment* comment);
    void addTag(const std::string& tag);

    std::string getTask() const;
};