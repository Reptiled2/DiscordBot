#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <functional>
#include <string>
#include "dpp/dpp.h"

template<typename T>
struct Command {
    std::string name;
    std::string description;
    bool NSFW;

    std::function<void(dpp::cluster&, const dpp::slashcommand_t&)> execute;
};

extern std::vector<Command<int>> commands;

void setupCommands();

#endif