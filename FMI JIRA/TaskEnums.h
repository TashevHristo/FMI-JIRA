#pragma once
#include <iostream>

enum class TaskType {
	Bug,
	Feature,
	Task,
	Improvement
};

enum class TaskPriority {
	Low,
	Medium,
	High,
	Critical
};

enum class TaskStatus {
	ToDo,
	InProgress,
	InReview,
	Done
};

inline std::string toString(TaskType type) {
	switch (type) {
	case TaskType::Bug: return "Bug";
	case TaskType::Feature: return "Feature";
	case TaskType::Improvement: return "Improvement";
	case TaskType::Task: return "Task";
	default:
		break;
	}
}

inline std::string toString(TaskPriority priority) {
	switch (priority) {
	case TaskPriority::Low: return "Low";
	case TaskPriority::Medium: return "Medium";
	case TaskPriority::High: return "High";
	case TaskPriority::Critical: return "Critical";
	default:
		break;
	}
}

inline std::string toString(TaskStatus status){
	switch(status){
	case TaskStatus::ToDo: return "ToDo";
	case TaskStatus::InProgress: return "InProgress";
	case TaskStatus::InReview: return "InReview";
	case TaskStatus::Done: return "Done";
	default:
		break;
	}
}