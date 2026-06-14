#include "AddCommentCommand.h"
#include "System.h"
#include <print>

void AddCommentCommand::execute(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2) {
        std::print("[Error] Usage: add-comment <task_id>\n");
        return;
    }
    System& sys = System::getInstance();

    auto studentResult = sys.getCurrentUser()->asStudent();
    if (!studentResult) { std::print("[Error] {}\n", studentResult.error()); return; }

    Project* project = sys.findProjectByTask(tokens[1]);
    if (!project) { std::print("[Error] Task '{}' not found.\n", tokens[1]); return; }

    std::string content;
    std::print("Comment: ");
    std::getline(std::cin, content);

    Comment* comment = new Comment(sys.getCurrentUser(), content, Date::today());
    auto result = studentResult.value()->addComment(*project, tokens[1], comment);
    if (!result) { std::print("[Error] {}\n", result.error()); return; }
    std::print("[System] Comment added.\n");
}

std::string AddCommentCommand::getName() const
{
    return "add-comment";
}
