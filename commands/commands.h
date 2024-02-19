#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H

#include <map>
#include <functional>
#include <string>
#include "dpp/dpp.h"


extern std::vector<std::pair<dpp::slashcommand, std::function<void(dpp::cluster&, const dpp::slashcommand_t&)>>> commands;

void setupCommands();

#endif