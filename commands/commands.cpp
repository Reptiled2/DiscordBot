#include <iostream>
#include <string>
#include <functional>
#include <vector>

#include "dpp/dpp.h"
#include "commands.h"


std::vector<std::pair<dpp::slashcommand, commandData>> commands;


void setupCommands() {

    // Ping
    {
        dpp::slashcommand command;
        command.name = "ping";
        command.description = "Returns client latency.";
        command.set_nsfw(false);

        commandData data;
        data.execute =
            [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
                event.reply(dpp::message(":ping_pong: Pong!"));
                return;
            };


        commands.emplace_back(command, data);
    };

    // Status
    {
        dpp::slashcommand command;
        command.name = "status";
        command.description = "Changes bot status.";
        command.set_nsfw(false);

        // Option
        {
            command.add_option(
                dpp::command_option(dpp::co_string, "type", "Bot status type", true)
                .add_choice(dpp::command_option_choice("Listening", std::string("listening")))
                .add_choice(dpp::command_option_choice("Watching", std::string("watching")))
                .add_choice(dpp::command_option_choice("Streaming", std::string("streaming")))
            );

            command.add_option(
                dpp::command_option(dpp::co_string, "message", "Bot status message", true)
            );
        };

        commandData data;
        data.ownerOnly = true;
        data.execute =
        [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
            std::string type = std::get<std::string>(event.get_parameter("type"));
            std::string message = std::get<std::string>(event.get_parameter("message"));
            

            dpp::activity_type activityType;
            if (type == "listening") {
                activityType = dpp::activity_type::at_listening;
            }
            else if (type == "watching") {
                activityType = dpp::activity_type::at_watching;
            }
            else if (type == "streaming") {
                activityType = dpp::activity_type::at_streaming;
            };


            bot.set_presence(dpp::presence(dpp::presence_status::ps_online, activityType, message));
            event.reply(dpp::message("Done!").set_flags(dpp::m_ephemeral));
        };


        commands.emplace_back(command, data);
    };
};