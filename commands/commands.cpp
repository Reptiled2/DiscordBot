#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "dpp/dpp.h"
#include "commands.h"

std::vector<Command<int>> commands;


void setupCommands() {

    // Ping
    {
        Command<int> command;
        command.name = "ping";
        command.description = "Returns client latency.";
        command.NSFW = true;
        command.execute = 
            [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
                event.reply(dpp::message(":ping_pong: Pong!"));
                return;
            };

        commands.push_back(command);
    }
}