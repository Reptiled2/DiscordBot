#include <dpp/dpp.h>
#include <string>
#include <vector>

#include "commands/commands.h"
#include "commands/commands.cpp"
#include "command_handler.h"


void handleCommands(dpp::cluster &bot, const dpp::slashcommand_t &event) {
};


void registerCommands(dpp::cluster &bot) {
	for (auto i = commands.begin(); i != commands.end(); i++) {
		std::cout << i->name;
	};
};

