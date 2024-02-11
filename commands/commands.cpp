#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "dpp/dpp.h"
#include "commands.h"


extern std::vector<Command<int>> commands;


int addCommand(const std::string& name, const std::string& description, bool NSFW, std::function<void(dpp::cluster&, const dpp::slashcommand_t&)> execute) {
    Command<int> command;
    command.name = name;
    command.description = description;
    command.NSFW = NSFW;
    command.execute = execute;

    commands.push_back(command);
    return 0;
}