#pragma once
#include "User.h"
#include "Roles.h"
#include "IStageManager.h"
#include "ITaskApprover.h"

class TeachingAssistant: public User, public ITaskApprover, public IStageManager {
public:
	TeachingAssistant(std::string username, std::string password);
	std::string getUsername() const override;
	Role getRole() const override;
	void viewProfile() const override;

	std::expected<ITaskApprover*, std::string> asTaskApprover() override;
	std::expected<IStageManager*, std::string> asStageManager() override;

	std::expected<void, std::string> approveTask(Project& project, const std::string& taskId) override;

	std::expected<void, std::string> reviewTask(Project& project, const std::string& taskId) override;

	std::expected<void, std::string> startStage(Project& project, const std::string& name) override;

	std::expected<void, std::string> endStage(Project& project, const std::string& name) override;

	std::expected<void, std::string> moveTaskToStage(Project& project, const std::string& taskId, const std::string& name) override;

	std::expected<void, std::string> stageReport(Project& project, const std::string& name) override;

};