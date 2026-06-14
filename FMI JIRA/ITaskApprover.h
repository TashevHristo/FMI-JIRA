#pragma once
#include <expected>
#include <iostream>
#include "Project.h"
 
struct ITaskApprover {
	virtual std::expected<void, std::string> approveTask(Project& project, const std::string& taskId) = 0;
	virtual std::expected<void, std::string> reviewTask(Project& project, const std::string& taskId) = 0;

	virtual ~ITaskApprover() = default;
};