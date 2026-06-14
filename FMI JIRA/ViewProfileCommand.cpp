#include "ViewProfileCommand.h"
#include <iostream>
#include <print>
#include <vector>
#include "System.h"

void ViewProfileCommand::execute(const std::vector<std::string>& tokens)
{
    User* user = System::getInstance().getCurrentUser();
    if (user == nullptr) {
        std::print("[Error] You must be logged in.\n");
        return;
    }
    user->viewProfile();
}

std::string ViewProfileCommand::getName() const
{
    return "view-profile";
}
