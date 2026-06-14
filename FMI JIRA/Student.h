#pragma once
#include "User.h"
#include "Roles.h"
#include "Project.h"
#include "Task.h"
#include "Comment.h"
#include "TaskEnums.h"
#include "Date.h"

class Student : public User {
public:
	Student(std::string username, std::string password);
	std::string getUsername() const override;
	Role getRole() const override;
	void viewProfile() const override;

	std::expected<Student*, std::string> asStudent() override;
	std::expected<void, std::string> joinProject(Project& project);
	std::expected<void, std::string> createTask(Project& project, std::string title, std::string description,
		TaskType type, TaskPriority priority, Date deadline);
	std::expected<void, std::string> assignTask(Project& project, const std::string& taskId);
	std::expected<void, std::string> changeStatus(Project& project, const std::string& taskId, TaskStatus status);
	std::expected<void, std::string> addComment(Project& project, const std::string& taskId, Comment* comment);
	std::expected<void, std::string> addTag(Project& project, const std::string& taskId, const std::string& tag);
	std::vector<Task*> getMyTasks(const Project& project) const;
	std::vector<Task*> getUpcomingTasks(const Project& project, const Date& before) const;

	std::vector<Task*> searchTasks(const Project& project, const std::string& keyword) const;
	std::vector<Task*> filterTasks(const Project& project, const std::string& criteria) const;
};