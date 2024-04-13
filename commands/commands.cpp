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
        commandData data;

        command.name = "status";
        command.description = "Changes bot status.";
        command.set_nsfw(false);

        data.ownerOnly = true;


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

    // Purge
    {
        dpp::slashcommand command;
        commandData data;

        command.name = "purge";
        command.description = "Purges the channel.";
        command.set_nsfw(false);
        
        data.requiredPermissions.push_back(dpp::permissions::p_manage_messages);


        // Option
        {
            command.add_option(
                dpp::command_option(dpp::command_option_type::co_integer, "amount", "Amount to delete message", true)                                                                       
            );
            command.add_option(
                dpp::command_option(dpp::command_option_type::co_channel, "channel", "Channel to delete messages from", false)
            );
        };

        
        data.execute =
            [](dpp::cluster& bot, const dpp::slashcommand_t& event) {
                const int64_t amount = std::get<int64_t>(event.get_parameter("amount"));

                dpp::snowflake channelId;
                try {
                    channelId = std::get<dpp::snowflake>(event.get_parameter("channel"));
                } catch (std::bad_variant_access& err) {
                    channelId = event.command.channel_id;
                };

                event.thinking(true);
                dpp::message_map messages = bot.messages_get_sync(channelId, 0, event.command.message_id, 0, amount);

                std::vector<dpp::snowflake> messagesVector;
                for (const auto& message : messages) {
                    if (message.second.sent + 1209600 < std::time(nullptr)) {
                        break;
                    };

                    messagesVector.push_back(message.first);
                };

                if (messagesVector.size() == 0) {
                    event.edit_original_response(dpp::message("Theres no message left to delete."));
                    return;
                };

                bot.message_delete_bulk_sync(messagesVector, channelId);

                event.edit_original_response(dpp::message("Successfully deleted " + std::to_string(messagesVector.size()) + " messages!"));
        };


        commands.emplace_back(command, data);
    };
};