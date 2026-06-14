#include "Stage.h"
#include <vector>

Stage::Stage(std::string name, Date startDate, Date endDate): name(std::move(name)), startDate(startDate), endDate(endDate)
{
	if (endDate <=> startDate == std::strong_ordering::less) {
		throw std::invalid_argument("The start date cannot be after the end date.");
	}
}

void Stage::addTask(Task* task)
{
	tasks.push_back(task);
}

std::expected<void, std::string> Stage::startStage() {
    if (status != StageStatus::Planned) {
        return std::unexpected("Only planned stage can be started.");
    }
    status = StageStatus::Active;
    return {};
}

std::expected<void, std::string> Stage::finishStage() {
    if (status != StageStatus::Active) {
        return std::unexpected("Only active stage can be finished.");
    }
    status = StageStatus::Finished;
    return {};
}

std::expected<void, std::string> Stage::removeTask(const std::string& taskId)
{
    auto removed = std::erase_if(tasks, [&taskId](const Task* task) {
        return task->getId() == taskId;
        });

    if (removed == 0) {
        return std::unexpected(std::format("No task with id: {} found", taskId));
    }
    return {};
}

std::string Stage::getStage() const
{
    return std::format("Stage: {}, Status: {}, Start date: {}, End date: {}", name, toString(status), startDate.getDate(), 
        endDate.getDate());
}

std::string Stage::getName() const
{
	return name;
}

const Date& Stage::getStartDate() const
{
	return startDate;
}

const Date& Stage::getEndDate() const
{
	return endDate;
}

const std::vector<Task*>& Stage::getTasks() const
{
	return tasks;
}

StageStatus Stage::getStatus() const
{
	return status;
}