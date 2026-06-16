#include "Administrator.h"

Administrator::Administrator(std::string username, std::string password) : User(std::move(username), std::move(password)) {}

std::string Administrator::getUsername() const
{
	return username;
}

Role Administrator::getRole() const
{
	return Role::Administrator;
}

void Administrator::viewProfile() const
{
	std::cout << std::format("Username: {}, Role: Administrator\n", username);
}

std::expected<IProjectManager*, std::string> Administrator::asProjectManager()
{
	return this;
}

std::expected<size_t, std::string> Administrator::createProject(std::vector<Project*>& projects, const std::string& name)
{
	for (Project* p : projects) {
		if (p->getName() == name)
			return std::unexpected(std::format("Project '{}' already exists.", name));
	}

	projects.push_back(new Project(name, ""));
	return {};
}

std::expected<void, std::string> Administrator::archiveProject(std::vector<Project*>& projects, const std::string& name)
{
	for (Project* p : projects) {
		if (p->getName() == name)
			return p->archive();
	}
	return std::unexpected(std::format("Project '{}' not found.", name));
}

std::expected<void, std::string> Administrator::addUser(std::vector<Project*>& projects, std::vector<User*>& users,
	const std::string& username, const std::string& projectName)
{
	User* user = nullptr;
	for (User* u : users) {
		if (u->getUsername() == username) {
			user = u;
			break;
		}
	}
	if (user == nullptr)
		return std::unexpected(std::format("User '{}' not found.", username));

	Project* project = nullptr;
	for (Project* p : projects) {
		if (p->getName() == projectName) {
			project = p;
			break;
		}
	}
	if (project == nullptr)
		return std::unexpected(std::format("Project '{}' not found.", projectName));


	if (project->findUser(username) != nullptr)
		return std::unexpected(std::format("User '{}' is already in project '{}'.", username, projectName));

	project->addUser(user);
	return {};
}

std::expected<void, std::string> Administrator::removeUser(std::vector<Project*>& projects, std::vector<User*>& users, 
	const std::string& username)
{
	User* userToDelete = nullptr;
	for (User* user : users) {
		if (user->getUsername() == username) {
			userToDelete = user;
			break;
		}
	}
	if (userToDelete == nullptr)
		return std::unexpected(std::format("User '{}' not found.", username));

	for (Project* project : projects) {
		project->removeUser(username);
	}

	std::erase_if(users, [&username](User* user) {
		return user->getUsername() == username;
		});

	delete userToDelete;
	return {};
}