#pragma once
#include "User.h"
#include "IProjectManager.h"
#include "Roles.h"

class Administrator : public User, public IProjectManager {
public:
	Administrator(std::string username, std::string password);
	std::string getUsername() const override;
	Role getRole() const override;
	void viewProfile() const override;

	std::expected<IProjectManager*, std::string> asProjectManager();

	std::expected<size_t, std::string> createProject(std::vector<Project*>& projects, const std::string& name) override;
	std::expected<void, std::string> archiveProject(std::vector<Project*>& projects, const std::string& name) override;
	std::expected<void, std::string> addUser(std::vector<Project*>& projects, std::vector<User*>& users, const std::string& username, const std::string& projectName) override;
	std::expected<void, std::string> removeUser(std::vector<Project*>& projects, std::vector<User*>& users, const std::string& username) override;

};