#pragma once
#include <vector>
#include <expected>
#include "ProjectStatus.h"

class User;
class Task;
class Stage;

class Project {
	std::string name;
	std::string description;
	std::vector<User*> users;
	std::vector<Task*> tasks;
	std::vector<Stage*> stages;
	ProjectStatus status = ProjectStatus::Active;
public:
	Project(std::string name, std::string description);

	std::expected<void, std::string> finalize();
	std::expected<void, std::string> archive();

	void addUser(User* user);
	void addTask(Task* task);
	void addStage(Stage* stage);

	std::expected<void, std::string> removeUser(const std::string& username);
	std::expected<void, std::string> removeTask(std::string taskId);

	const std::string getProject() const;
	const std::string getName() const;
	ProjectStatus getStatus() const;
	const std::vector<User*> getUsers() const;
	const std::vector<Task*> getTasks() const;
	const std::vector<Stage*> getStages() const;

	User* findUser(const std::string& username) const;
	Task* findTask(const std::string& taskId) const;
	Stage* findStage(const std::string& stageName) const;
};