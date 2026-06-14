#pragma once
#include "User.h"
#include "Roles.h"
#include "IStageManager.h"
#include "ITaskApprover.h"

class Lecturer : public User, public ITaskApprover, public IStageManager {
public:
	Lecturer(std::string username, std::string password);
	std::string getUsername() const override;
	Role getRole() const override;
	void viewProfile() const override;

	std::expected<void, std::string> approveTask(Project& project, const std::string& taskId) override;
	std::expected<void, std::string> reviewTask(Project& project, const std::string& taskId) override;

	std::expected<void, std::string> startStage(Project& project, const std::string& name) override;
	std::expected<void, std::string> endStage(Project& project, const std::string& name) override;
	std::expected<void, std::string> moveTaskToStage(Project& project, const std::string& taskId, const std::string& name) override;
	std::expected<void, std::string> stageReport(Project& project, const std::string& name) override;

	std::expected<void, std::string> gradeTask(Project& project, const std::string& taskId, double grade);
	std::expected<void, std::string> finalizeProject(Project& project);
	void studentReport(const Project& project, const std::string& username) const;
	std::expected<ITaskApprover*, std::string> asTaskApprover() override;
	std::expected<IStageManager*, std::string> asStageManager() override;
	std::expected<Lecturer*, std::string> asLecturer() override;
};