#pragma once

#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <functional>
#include <string>
#include "dpp/dpp.h"

struct commandData {
    bool ownerOnly = false;
    std::vector<dpp::permissions> requiredPermissions;

    std::function<void(dpp::cluster&, const dpp::slashcommand_t&)> execute;
};

extern std::vector<std::pair<dpp::slashcommand, commandData>> commands;

void setupCommands();

#endif