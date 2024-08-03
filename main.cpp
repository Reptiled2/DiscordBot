#include <dpp/dpp.h>
#include <iostream>
#include <string>
#include <vector>

#include "commands/commands.h"
#include "command_handler.h"


const static std::string BOT_TOKEN = "";


int main() {
	dpp::cluster bot(BOT_TOKEN);
	bot.on_log(dpp::utility::cout_logger());


	bot.on_ready([&bot](const dpp::ready_t &event) {
		bot.set_presence(dpp::presence::presence(dpp::presence_status::ps_idle, dpp::activity_type::at_custom, "Booting up..."));

		if (dpp::run_once<struct register_bot_commands>()) {
			std::cout << "Registering commands...\n";
			setupCommands();
			registerCommands(bot);
			std::cout << "Registered commands.\n";
		};

		bot.set_presence(dpp::presence::presence(dpp::presence_status::ps_online, dpp::activity_type::at_listening, ""));
		std::cout << "Bot is up and running!\n";
		return;
	});


	bot.on_slashcommand([&bot](const dpp::slashcommand_t &event) {
		handleCommands(bot, event);
		return;
	});


	bot.start(dpp::st_wait);

	return 0;
};
