#pragma once
#include <vector>
#include <iostream>

struct Command {
    virtual void execute(const std::vector<std::string>& tokens) = 0;
    virtual std::string getName() const = 0;
    virtual ~Command() = default;
};