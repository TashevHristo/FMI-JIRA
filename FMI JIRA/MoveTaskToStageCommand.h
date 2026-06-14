#pragma once
#include <iostream>
#include <vector>
#include "Command.h"

struct MoveTaskToStageCommand : public Command {
	void execute(const std::vector<std::string>& tokens) override;
	std::string getName() const override;
};