#pragma once
#include <iostream>

enum class StageStatus {
	Planned,
	Active,
	Finished
};

inline std::string toString(StageStatus status) {
	switch (status)
	{
	case StageStatus::Planned: return "Planned";
	case StageStatus::Active: return "Active";
	case StageStatus::Finished: return "Finished";
	default:
		break;
	}
}