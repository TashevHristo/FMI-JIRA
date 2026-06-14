#pragma once
#include <expected>
#include <iostream>
#include "ProjectStatus.h"
#include "Project.h"
#include "User.h"

struct IProjectManager {
	virtual std::expected<size_t, std::string> createProject(std::vector<Project*>& projects, const std::string& name) = 0;
	virtual std::expected<void, std::string> archiveProject(std::vector<Project*>& projects, const std::string& name) = 0;
	virtual std::expected<void, std::string> addUser(std::vector<Project*>& projects, std::vector<User*>& users, 
		const std::string& username, const std::string& projectName) = 0;
	virtual std::expected<void, std::string> removeUser(std::vector<Project*>& projects, std::vector<User*>& users,
		const std::string& username) = 0;
    
	virtual ~IProjectManager() = default;
};