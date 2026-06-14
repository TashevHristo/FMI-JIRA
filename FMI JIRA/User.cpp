#include "User.h"
#include <string>
#include <iostream>
#include "Roles.h"

User::User(std::string username, std::string password): id(id_generator++), username(std::move(username)), 
password(std::move(password))
{}

std::string User::getPassword() const
{
	return password;
}

std::expected<ITaskApprover*, std::string> User::asTaskApprover()
{
	return std::unexpected(std::format("The {} is not allowed to approve tasks.", toString(getRole())));
}

std::expected<IStageManager*, std::string> User::asStageManager()
{
	return std::unexpected(std::format("The {} is not allowed to manage stages.", toString(getRole())));
}

std::expected<IProjectManager*, std::string> User::asProjectManager()
{
	return std::unexpected(std::format("The {} is not allowed to manage projects.", toString(getRole())));
}

std::expected<Student*, std::string> User::asStudent()
{
	return std::unexpected(std::format("The {} is not allowed to perform student actions.", toString(getRole())));
}

std::expected<Lecturer*, std::string> User::asLecturer()
{
	return std::unexpected(std::format("The {} is not allowed to perform lecturer actions.", toString(getRole())));
}

size_t User::id_generator = 1;