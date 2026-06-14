#include <iostream>
#include "System.h"
#include "CommandHandler.h"
#include <print>
#include <string>

int main()
{
    CommandHandler handler;

    std::string input;
    while (true) {
        std::print("> ");
        std::getline(std::cin, input);
        if (!handler.execute(input)) break;
    }
    return 0;
}