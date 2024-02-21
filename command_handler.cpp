#include <dpp/dpp.h>
#include <string>
#include <vector>

#include <dpp/dpp.h>
#include "commands/commands.h"
#include "command_handler.h"


void handleCommands(dpp::cluster &bot, const dpp::slashcommand_t &event) {

	if (event.command.get_issuing_user().is_bot()) {
		event.cancel_event();
		return;
	};

	for (auto i = commands.begin(); i != commands.end(); i++) {
		if (i->first.name == event.command.get_command_name()) {

			if (i->first.nsfw && !event.command.channel.is_nsfw()) {
				event.reply(dpp::message("You can only use this command on NSFW channels!").set_flags(dpp::m_ephemeral));
				return;
			};


			if (i->second.ownerOnly && event.command.get_issuing_user().id != 486198835975028757) {
				event.reply(dpp::message("You can't use this command!").set_flags(dpp::m_ephemeral));
				return;
			};

			i->second.execute(bot, event);
			return;
		}
	}

};


void registerCommands(dpp::cluster &bot) {
	std::vector<dpp::slashcommand> commandList;
	for (auto i = commands.begin(); i != commands.end(); i++) {
		commandList.push_back(i->first);
	};

	bot.global_bulk_command_create_sync(commandList);
};

