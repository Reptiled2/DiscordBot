#include <dpp/dpp.h>
#include <iostream>
#include <string>
#include <vector>

#include "commands/commands.h"
#include "command_handler.h"


const static std::string BOT_TOKEN = "MTA1MDQyMjM4OTA0NzA0MjA5MA.G-c88_.XaYbAdeFzlGPQDlsO-orr2eCBAG7MMVqovRkik";


int main() {
	dpp::cluster bot(BOT_TOKEN);
	bot.on_log(dpp::utility::cout_logger());


	bot.on_ready([&bot](const dpp::ready_t &event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			std::cout << "Registering commands...\n";
			setupCommands();
			registerCommands(bot);
			std::cout << "Registered commands.\n";
		};

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