#include <dpp/dpp.h>
#include <string>
#include <vector>

#include <dpp/dpp.h>
#include "commands/commands.h"
#include "command_handler.h"


void handleCommands(dpp::cluster &bot, const dpp::slashcommand_t &event) {
	for (auto i = commands.begin(); i != commands.end(); i++) {
		if (i->name == event.command.get_command_name()) {

			if (i->NSFW && !event.command.channel.is_nsfw()) {
				event.reply(dpp::message("You can only use this command on NSFW channels!").set_flags(dpp::m_ephemeral));
				return;
			};


			i->execute(bot, event);
			return;
		}
	}

};


void registerCommands(dpp::cluster &bot) {
	bot.global_bulk_command_delete_sync();

	dpp::slashcommand_map currentCommands = bot.global_commands_get_sync();
	std::vector<dpp::slashcommand> commandList;

	for (auto i = commands.begin(); i != commands.end(); i++) {
		dpp::slashcommand command;
		command.name = i->name;
		command.description = i->description;
		command.set_nsfw(i->NSFW);

		commandList.push_back(command);
	};

	bot.global_bulk_command_create(commandList);
};

