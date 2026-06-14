#pragma once
#include <expected>
#include <iostream>
#include "Project.h"

struct IStageManager {
	virtual std::expected<void, std::string> startStage(Project& project, const std::string& name) = 0;
	virtual std::expected<void, std::string> endStage(Project& project, const std::string& name) = 0;
	virtual std::expected<void, std::string> moveTaskToStage(Project& project, const std::string& taskId, const std::string& name) = 0;
	virtual std::expected<void, std::string> stageReport(Project& project, const std::string& name) = 0;

	virtual ~IStageManager() = default;
};