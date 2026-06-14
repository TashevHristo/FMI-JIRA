#pragma once
#include <iostream>

enum class Role {
	Student,
	TeachingAssistant,
	Lecturer,
	Administrator
};

inline std::string toString(Role role) {
	switch (role) {
	case Role::Student: return "Student";
	case Role::TeachingAssistant: return "Teaching Assistant";
	case Role::Lecturer: return "Lecturer";
	case Role::Administrator: return "Administrator";
	default:
		throw std::invalid_argument("Unknown value.");
	}
}