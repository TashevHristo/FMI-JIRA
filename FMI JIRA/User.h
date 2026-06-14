#pragma once
#include <expected>
#include <string>
#include "ITaskApprover.h"
#include "IStageManager.h"
#include "IProjectManager.h"
#include "Roles.h"

class Student;
class Lecturer;

class User {
protected:
	size_t id;
	std::string username;
	std::string password;

	User(std::string username, std::string password);

public:
	static size_t id_generator;
	virtual std::string getUsername() const = 0;
	virtual Role getRole() const = 0;
	virtual std::string getPassword() const;
	virtual void viewProfile() const = 0;

	virtual std::expected<ITaskApprover*, std::string> asTaskApprover();
	virtual std::expected<IStageManager*, std::string> asStageManager();
	virtual std::expected<IProjectManager*, std::string> asProjectManager();
	virtual std::expected<Student*, std::string> asStudent();
	virtual std::expected<Lecturer*, std::string> asLecturer();

	virtual ~User() = default;
};