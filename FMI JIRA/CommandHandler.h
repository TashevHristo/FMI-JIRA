#pragma once
#include "Command.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

class CommandHandler {
    std::unordered_map<std::string, Command*> commands;
    void registerCommand(Command* command);
    std::vector<std::string> parseInput(const std::string& input) const;

public:
    CommandHandler();
    ~CommandHandler();
    bool execute(const std::string& input);
};
