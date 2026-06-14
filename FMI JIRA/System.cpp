#include "System.h"
#include <fstream>
#include <sstream>
#include "ParseHelpers.h"
#include "Stage.h"
#include <print>
#include "Comment.h"

User* System::findUser(const std::string& username) const
{
	for (auto& user : users) {
		if (user->getUsername() == username) return user;
	}
	return nullptr;
}

Project* System::findProject(const std::string& name) const
{
	for (auto& project : projects) {
		if (project->getName() == name) return project;
	}
	return nullptr;
}

Task* System::findTaskGlobally(const std::string& taskId) const
{
	for (auto& project : projects) {
		Task* task = project->findTask(taskId);
		if (task != nullptr) return task;
	}
	return nullptr;
}

Project* System::findProjectByTask(const std::string& taskId) const
{
	for (auto& project : projects) {
		if (project->findTask(taskId) != nullptr) return project;
	}
	return nullptr;
}

Project* System::findProjectByStage(const std::string& stageName) const
{
	for (Project* project : projects) {
		if (project->findStage(stageName) != nullptr) return project;
	}
	return nullptr;
}

System::System()
{
	users.push_back(new Administrator("admin", "admin"));

	load();
}

std::expected<void, std::string> System::login(const std::string& username, const std::string& password)
{
	if (currentUser != nullptr)
		return std::unexpected("Already logged in. Please logout first.");

	User* user = findUser(username);
	if (user == nullptr)
		return std::unexpected(std::format("User '{}' not found.", username));

	if (user->getPassword() != password)
		return std::unexpected("Incorrect password.");

	currentUser = user;
	return {};
}

std::expected<void, std::string> System::logout()
{
	if (currentUser == nullptr)
		return std::unexpected("No user is logged in.");

	currentUser = nullptr;
	return {};
}

std::expected<void, std::string> System::registerUser(const std::string& username, const std::string& password, Role role)
{
	if (currentUser == nullptr)
		return std::unexpected("You must be logged in to register users.");

	if (currentUser->getRole() != Role::Administrator)
		return std::unexpected("Only Administrator can register users.");

	if (findUser(username) != nullptr)
		return std::unexpected(std::format("User '{}' already exists.", username));

	switch (role) {
	case Role::Student:
		users.push_back(new Student(username, password));
		break;
	case Role::TeachingAssistant:
		users.push_back(new TeachingAssistant(username, password));
		break;
	case Role::Lecturer:
		users.push_back(new Lecturer(username, password));
		break;
	case Role::Administrator:
		return std::unexpected("Cannot register another Administrator.");
	}
	return {};
}

User* System::getCurrentUser() const
{
	return currentUser;
}

std::vector<User*>& System::getUsers()
{
	return users;
}

std::vector<Project*>& System::getProjects()
{
	return projects;
}

std::expected<void, std::string> System::save() const
{
	{
		std::ofstream file("generators.txt");
		if (!file) return std::unexpected("Cannot open generators.txt for writing.");
		file << Task::id_generator << "\n";
		file << User::id_generator << "\n";
	}

	{
		std::ofstream file("users.txt");
		if (!file) return std::unexpected("Cannot open users.txt for writing.");
		for (User* u : users) {

			if (u->getRole() == Role::Administrator) continue;
			file << u->getUsername() << "|"
				<< u->getPassword() << "|"
				<< toString(u->getRole()) << "\n";
		}
	}

	{
		std::ofstream file("tasks.txt");
		if (!file) return std::unexpected("Cannot open tasks.txt for writing.");
		for (Project* p : projects) {
			for (Task* t : p->getTasks()) {
				file << t->getId() << "|"
					<< t->getTitle() << "|"
					<< t->getDescription() << "|"
					<< toString(t->getType()) << "|"
					<< toString(t->getPriority()) << "|"
					<< toString(t->getStatus()) << "|"
					<< t->getDeadline().getDate() << "|"
					<< t->getGrade() << "|"
					<< p->getName() << "|"
					<< (t->getUserInCharge() ? t->getUserInCharge()->getUsername() : "none") << "\n";
			}
		}
	}

	{
		std::ofstream file("projects.txt");
		if (!file) return std::unexpected("Cannot open projects.txt for writing.");
		for (Project* p : projects) {
			file << p->getName() << "|"
				<< toString(p->getStatus()) << "|";
			for (User* u : p->getUsers()) file << u->getUsername() << ",";
			file << "\n";
		}
	}

	{
		std::ofstream file("stages.txt");
		if (!file) return std::unexpected("Cannot open stages.txt for writing.");
		for (Project* p : projects) {
			for (Stage* s : p->getStages()) {
				file << p->getName() << "|"
					<< s->getName() << "|"
					<< toString(s->getStatus()) << "|"
					<< s->getStartDate().getDate() << "|"
					<< s->getEndDate().getDate() << "|";
				for (Task* t : s->getTasks()) file << t->getId() << ",";
				file << "\n";
			}
		}
	}

	{
		std::ofstream file("comments.txt");
		if (!file) return std::unexpected("Cannot open comments.txt for writing.");
		for (Project* p : projects) {
			for (Task* t : p->getTasks()) {
				for (Comment* c : t->getComments()) {
					file << t->getId() << "|"
						<< c->getAuthor()->getUsername() << "|"
						<< c->getDate().getDate() << "|"
						<< c->getContent() << "\n";
				}
			}
		}
	}

	{
		std::ofstream file("tags.txt");
		if (!file) return std::unexpected("Cannot open tags.txt for writing.");
		for (Project* p : projects) {
			for (Task* t : p->getTasks()) {
				for (const std::string& tag : t->getTags()) {
					file << t->getId() << "|" << tag << "\n";
				}
			}
		}
	}

	return {};
}

std::expected<void, std::string> System::load()
{
	{
		std::ifstream file("generators.txt");
		if (file) {
			file >> Task::id_generator;
			file >> User::id_generator;
		}
	}

	{
		std::ifstream file("users.txt");
		if (file) {
			std::string line;
			while (std::getline(file, line)) {
				if (line.empty()) continue;
				std::istringstream ss(line);
				std::string username, password, role;
				std::getline(ss, username, '|');
				std::getline(ss, password, '|');
				std::getline(ss, role, '|');

				if (findUser(username)) continue;

				if (role == "Student")
					users.push_back(new Student(username, password));
				else if (role == "Teaching Assistant")
					users.push_back(new TeachingAssistant(username, password));
				else if (role == "Lecturer")
					users.push_back(new Lecturer(username, password));
			}
		}
	}

	{
		std::ifstream file("projects.txt");
		if (file) {
			std::string line;
			while (std::getline(file, line)) {
				if (line.empty()) continue;
				std::istringstream ss(line);
				std::string name, status, membersStr;
				std::getline(ss, name, '|');
				std::getline(ss, status, '|');
				std::getline(ss, membersStr, '|');

				if (findProject(name)) continue;

				Project* project = new Project(name, "");
				projects.push_back(project);

				if (status == "Finished") project->finalize();
				else if (status == "Archived") { project->finalize(); project->archive(); }

				std::istringstream memberStream(membersStr);
				std::string uname;
				while (std::getline(memberStream, uname, ',')) {
					if (uname.empty()) continue;
					User* user = findUser(uname);
					if (user) project->addUser(user);
				}
			}
		}
	}

	{
		std::ifstream file("tasks.txt");
		if (file) {
			std::string line;
			while (std::getline(file, line)) {
				if (line.empty()) continue;
				std::istringstream ss(line);
				std::string id, title, description, type, priority, status,
					deadline, gradeStr, projectName, assignee;
				std::getline(ss, id, '|');
				std::getline(ss, title, '|');
				std::getline(ss, description, '|');
				std::getline(ss, type, '|');
				std::getline(ss, priority, '|');
				std::getline(ss, status, '|');
				std::getline(ss, deadline, '|');
				std::getline(ss, gradeStr, '|');
				std::getline(ss, projectName, '|');
				std::getline(ss, assignee, '|');

				Project* project = findProject(projectName);
				if (!project) continue;

				Date d = Date::parse(deadline);
				Task* task = new Task(title, description,
					parseTaskType(type), parseTaskPriority(priority), d);

				if (status == "InProgress") {
					task->changeStatus(TaskStatus::InProgress);
				}
				else if (status == "InReview") {
					task->changeStatus(TaskStatus::InProgress);
					task->changeStatus(TaskStatus::InReview);
				}
				else if (status == "Done") {
					task->changeStatus(TaskStatus::InProgress);
					task->changeStatus(TaskStatus::InReview);
					task->changeStatus(TaskStatus::Done);
				}

				double grade = std::stod(gradeStr);
				if (grade > 0.0) task->setGrade(grade);

				if (assignee != "none") {
					User* user = findUser(assignee);
					if (user) task->assignUser(user);
				}

				project->addTask(task);
			}
		}
	}

	{
		std::ifstream file("stages.txt");
		if (file) {
			std::string line;
			while (std::getline(file, line)) {
				if (line.empty()) continue;
				std::istringstream ss(line);
				std::string projectName, stageName, status, startStr, endStr, tasksStr;
				std::getline(ss, projectName, '|');
				std::getline(ss, stageName, '|');
				std::getline(ss, status, '|');
				std::getline(ss, startStr, '|');
				std::getline(ss, endStr, '|');
				std::getline(ss, tasksStr, '|');

				Project* project = findProject(projectName);
				if (!project) continue;

				if (project->findStage(stageName)) continue;

				try {
					Date start = Date::parse(startStr);
					Date end = Date::parse(endStr);
					Stage* stage = new Stage(stageName, start, end);

					if (status == "Active") stage->startStage();
					else if (status == "Finished") {
						stage->startStage();
						stage->finishStage();
					}

					std::istringstream taskStream(tasksStr);
					std::string taskId;
					while (std::getline(taskStream, taskId, ',')) {
						if (taskId.empty()) continue;
						Task* task = findTaskGlobally(taskId);
						if (task) stage->addTask(task);
					}

					project->addStage(stage);
				}
				catch (const std::invalid_argument& e) {
					std::print("[Error] Failed to load stage '{}': {}\n", stageName, e.what());
				}
			}
		}
	}

	{
		std::ifstream file("comments.txt");
		if (file) {
			std::string line;
			while (std::getline(file, line)) {
				if (line.empty()) continue;
				std::istringstream ss(line);
				std::string taskId, authorName, dateStr, content;
				std::getline(ss, taskId, '|');
				std::getline(ss, authorName, '|');
				std::getline(ss, dateStr, '|');
				std::getline(ss, content);

				Task* task = findTaskGlobally(taskId);
				User* author = findUser(authorName);
				if (!task || !author) continue;

				try {
					Date date = Date::parse(dateStr);
					task->addComment(new Comment(author, content, date));
				}
				catch (const std::invalid_argument&) { continue; }
			}
		}
	}

	{
		std::ifstream file("tags.txt");
		if (file) {
			std::string line;
			while (std::getline(file, line)) {
				if (line.empty()) continue;
				std::istringstream ss(line);
				std::string taskId, tag;
				std::getline(ss, taskId, '|');
				std::getline(ss, tag);

				Task* task = findTaskGlobally(taskId);
				if (task) task->addTag(tag);
			}
		}
	}

	return {};
}

System::~System()
{
	for (auto& user : users) delete user;
	for (auto& project : projects) delete project;
}
