#pragma once
#include "Command.h"
#include <vector>
#include <iostream>

struct LoginCommand : Command {
	void execute(const std::vector<std::string>& tokens) override;
	std::string getName() const override;
};