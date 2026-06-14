#include "CommandHandler.h"
#include "System.h"
#include <print>
#include <sstream>

#include "LoginCommand.h"
#include "LogoutCommand.h"
#include "ViewProfileCommand.h"

#include "JoinProjectCommand.h"
#include "ListProjectsCommand.h"
#include "ListTasksCommand.h"
#include "CreateTaskCommand.h"
#include "AssignTaskCommand.h"
#include "ChangeStatusCommand.h"
#include "AddCommentCommand.h"
#include "MyTasksCommand.h"
#include "SearchTasksCommand.h"
#include "FilterTasksCommand.h"
#include "AddTagCommand.h"
#include "UpcomingTasksCommand.h"

#include "ApproveTaskCommand.h"
#include "ReviewTaskCommand.h"
#include "StartStageCommand.h"
#include "FinishStageCommand.h"
#include "MoveTaskToStageCommand.h"
#include "StageReportCommand.h"
#include "ChangePriorityCommand.h"

#include "ListAllProjectsCommand.h"
#include "ListAllTasksCommand.h"
#include "GradeTaskCommand.h"
#include "StudentReportCommand.h"
#include "FinalizeProjectCommand.h"

#include "CreateProjectCommand.h"
#include "ArchiveProjectCommand.h"
#include "AddUserToProjectCommand.h"
#include "RemoveUserCommand.h"
#include "RegisterCommand.h"
#include "SaveCommand.h"
#include "LoadCommand.h"

CommandHandler::CommandHandler()
{

    registerCommand(new LoginCommand());
    registerCommand(new LogoutCommand());
    registerCommand(new ViewProfileCommand());

    registerCommand(new JoinProjectCommand());
    registerCommand(new ListProjectsCommand());
    registerCommand(new ListTasksCommand());
    registerCommand(new CreateTaskCommand());
    registerCommand(new AssignTaskCommand());
    registerCommand(new ChangeStatusCommand());
    registerCommand(new AddCommentCommand());
    registerCommand(new MyTasksCommand());
    registerCommand(new SearchTasksCommand());
    registerCommand(new FilterTasksCommand());
    registerCommand(new AddTagCommand());
    registerCommand(new UpcomingTasksCommand());

    registerCommand(new ApproveTaskCommand());
    registerCommand(new ReviewTaskCommand());
    registerCommand(new StartStageCommand());
    registerCommand(new FinishStageCommand());
    registerCommand(new MoveTaskToStageCommand());
    registerCommand(new StageReportCommand());
    registerCommand(new ChangePriorityCommand());

    registerCommand(new ListAllProjectsCommand());
    registerCommand(new ListAllTasksCommand());
    registerCommand(new GradeTaskCommand());
    registerCommand(new StudentReportCommand());
    registerCommand(new FinalizeProjectCommand());

    registerCommand(new CreateProjectCommand());
    registerCommand(new ArchiveProjectCommand());
    registerCommand(new AddUserToProjectCommand());
    registerCommand(new RemoveUserCommand());
    registerCommand(new RegisterCommand());
    registerCommand(new SaveCommand());
    registerCommand(new LoadCommand());
}

void CommandHandler::registerCommand(Command* command)
{
    commands[command->getName()] = command;
}

CommandHandler::~CommandHandler()
{
    for (auto& [name, cmd] : commands) delete cmd;
}

bool CommandHandler::execute(const std::string& input)
{
    if (input.empty()) return true;

    std::vector<std::string> tokens = parseInput(input);
    if (tokens.empty()) return true;

    if (tokens[0] == "close") {
        std::print("[System] System shutting down...\n");
        return false;
    }


    if (tokens[0] != "login" && System::getInstance().getCurrentUser() == nullptr) {
        std::print("[Error] You must be logged in.\n");
        return true;
    }

    auto it = commands.find(tokens[0]);
    if (it == commands.end()) {
        std::print("[Error] Unknown command: {}\n", tokens[0]);
        return true;
    }

    it->second->execute(tokens);
    return true;
}

std::vector<std::string> CommandHandler::parseInput(const std::string& input) const
{
    std::vector<std::string> tokens;
    std::istringstream stream(input);
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}