#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "dpp/dpp.h"
#include "commands.h"

std::vector<std::pair<dpp::slashcommand, std::function<void(dpp::cluster&, const dpp::slashcommand_t&)>>> commands;


void setupCommands() {

    // Ping
    {
        dpp::slashcommand command;
        command.name = "ping";
        command.description = "Returns client latency.";
        command.set_nsfw(false);

        commands.emplace_back(command,
            [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
                event.reply(dpp::message(":ping_pong: Pong!"));
                return;
            }
        );   
    }
}