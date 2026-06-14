#pragma once
#include <iostream>

enum class ProjectStatus {
	Active,
	Finished,
	Archived
};

inline std::string toString(ProjectStatus status) {
	switch (status) {
	case ProjectStatus::Active: return "Active";
	case ProjectStatus::Finished: return "Finished";
	case ProjectStatus::Archived: return "Archived";
	default:
		break;
	}
}