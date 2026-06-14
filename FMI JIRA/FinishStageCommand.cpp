#include "FinishStageCommand.h"
#include "System.h"
#include <print>

void FinishStageCommand::execute(const std::vector<std::string>& tokens)
{
    if (tokens.size() < 2) {
        std::print("[Error] Usage: finish-stage <stage_name>\n");
        return;
    }
    System& sys = System::getInstance();

    auto managerResult = sys.getCurrentUser()->asStageManager();
    if (!managerResult) { 
        std::print("[Error] {}\n", managerResult.error()); 
        return; 
    }

    Project* project = sys.findProjectByStage(tokens[1]);
    if (!project) { 
        std::print("[Error] Stage '{}' not found.\n", tokens[1]); 
        return; 
    }

    auto result = managerResult.value()->endStage(*project, tokens[1]);
    if (!result) { std::print("[Error] {}\n", result.error()); return; }
    std::print("[System] Stage '{}' finished.\n", tokens[1]);
}

std::string FinishStageCommand::getName() const
{
    return "finish-stage";
}
