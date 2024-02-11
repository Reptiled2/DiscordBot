#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <dpp/dpp.h>
#include <string>

void handleCommands(dpp::cluster& bot, const dpp::slashcommand_t& event);

void registerCommands(dpp::cluster& bot);

#endif