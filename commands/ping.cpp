#include "commands.h"
#include "commands.cpp"
#include <dpp/dpp.h>


void execute(dpp::cluster &bot, const dpp::slashcommand_t &event) {
    event.reply(dpp::message(":ping_pong: Pong!"));
    return;
};

int temp = addCommand(
    "ping",
    "Returns client latency.",
    false,
    execute
);