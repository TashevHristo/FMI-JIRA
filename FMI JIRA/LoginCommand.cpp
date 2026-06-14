#include "LoginCommand.h"
#include "System.h"
#include <iostream>
#include <print>

void LoginCommand::execute(const std::vector<std::string>& tokens)
{
	if (tokens.size() < 3) {
		std::print("[Error] Usage: login <username> <password>\n");
		return;
	}

	auto result = System::getInstance().login(tokens[1], tokens[2]);
	if (!result) {
		std::print("[Error] {}\n", result.error());
		return;
	}
	std::print("[System] Successfully logged in. Role: {}.\n", toString(System::getInstance().getCurrentUser()->getRole()));
}

std::string LoginCommand::getName() const
{
	return "login";
}
