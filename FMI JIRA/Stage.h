#pragma once
#include <vector>
#include <expected>
#include "Date.h"
#include "Task.h"
#include "StageStatus.h"

class Stage {
	std::string name;
	Date startDate;
	Date endDate;
	std::vector<Task*> tasks;
	StageStatus status = StageStatus::Planned;
public:
	Stage(std::string name, Date startDate, Date endDate);

	void addTask(Task* task);
	std::expected<void, std::string> startStage();
	std::expected<void, std::string> finishStage();

	std::expected<void, std::string> removeTask(const std::string& taskId);

	std::string getStage() const;
	std::string getName() const;
	const Date& getStartDate() const;
	const Date& getEndDate() const;
	const std::vector<Task*>& getTasks() const;
	StageStatus getStatus() const;
};