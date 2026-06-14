#include "Task.h"
#include <iostream>
#include <string>
#include "TaskEnums.h"
#include "Comment.h"

Task::Task(std::string title, std::string description, TaskType type, TaskPriority priority, Date deadline): 
	id(std::format("FMI-{}",id_generator++)), title(std::move(title)), description(std::move(description)), 
	type(type), priority(priority), deadline(deadline){}

size_t Task::id_generator = 101;

std::string Task::getId() const
{
	return id;
}

std::string Task::getTitle() const
{
	return title;
}

std::string Task::getDescription() const
{
	return description;
}

TaskType Task::getType() const
{
	return type;
}

TaskPriority Task::getPriority() const
{
	return priority;
}

TaskStatus Task::getStatus() const
{
	return status;
}

User* Task::getUserInCharge() const
{
	return userInCharge;
}

double Task::getPoints() const
{
	return points;
}

double Task::getGrade() const
{
	return grade;
}

const std::vector<Comment*>& Task::getComments() const
{
	return comments;
}

const Date& Task::getDeadline() const
{
	return deadline;
}

const std::vector<std::string>& Task::getTags() const
{
	return tags;
}

const std::vector<std::string>& Task::getHistory() const
{
	return history;
}

std::expected<void, std::string> Task::changeStatus(TaskStatus newStatus)
{
	if (status == TaskStatus::Done) {
		return std::unexpected("Cannot change the status of a task that has already been completed.");
	}
	history.push_back(std::format("Status changed: {} -> {}",
		toString(status), toString(newStatus)));
	status = newStatus;
	return {};
}

void Task::changePriority(TaskPriority newPriority)
{
	history.push_back(std::format("Priority changed: {} -> {}", toString(priority), toString(newPriority)));
	priority = newPriority;
}

void Task::assignUser(User* user)
{
	userInCharge = user;
}

std::expected<void, std::string> Task::setGrade(double grade)
{
	if (grade < 2.0 || grade > 6.0) return std::unexpected("Invalid  grade.");
	this->grade = grade;
	return {};
}

void Task::addComment(Comment* comment)
{
	comments.push_back(comment);
}

void Task::addTag(const std::string& tag)
{
	tags.push_back(tag);
}

std::string Task::getTask() const
{
	return std::format("{} | {} | {}", title, toString(status), toString(priority));
}