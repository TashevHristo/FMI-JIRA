// System.h
#pragma once
#include <vector>
#include <expected>
#include "User.h"
#include "Project.h"
#include "Student.h"
#include "TeachingAssistant.h"
#include "Lecturer.h"
#include "Administrator.h"

class System {
    std::vector<User*> users;
    std::vector<Project*> projects;
    User* currentUser = nullptr;

    System();
    System(const System&) = delete;
    System& operator=(const System&) = delete;
public:
    static System& getInstance() {
        static System instance;
        return instance;
    }

    std::expected<void, std::string> login(const std::string& username, const std::string& password);
    std::expected<void, std::string> logout();
    std::expected<void, std::string> registerUser(const std::string& username, const std::string& password, Role role);

    User* getCurrentUser() const;
    std::vector<User*>& getUsers();
    std::vector<Project*>& getProjects();

    User* findUser(const std::string& username) const;
    Project* findProject(const std::string& name) const;
    Task* findTaskGlobally(const std::string& taskId) const;
    Project* findProjectByTask(const std::string& taskId) const;
    Project* findProjectByStage(const std::string& stageName) const;

    std::expected<void, std::string> save() const;
    std::expected<void, std::string> load();

    ~System();
};