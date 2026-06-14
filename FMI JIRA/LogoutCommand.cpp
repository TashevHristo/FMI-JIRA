#include "LogoutCommand.h"
#include <iostream>
#include <print>
#include "System.h"

void LogoutCommand::execute(const std::vector<std::string>& tokens)
{
    auto result = System::getInstance().logout();
    if (!result) { 
        std::print("[Error] {}\n", result.error()); 
        return; 
    }
    std::print("[System] Successfully logged out.\n");
}

std::string LogoutCommand::getName() const
{
    return "logout";
}
