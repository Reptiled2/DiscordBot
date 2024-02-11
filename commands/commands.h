#ifndef COMMANDS_H
#define COMMANDS_H

#include "ping.h"
#include <map>
#include <functional>
#include <string>
#include "dpp/dpp.h"

template<typename T>
struct Command {
    std::string name;
    std::string description;
    bool NSFW;

    std::function<void(dpp::cluster&, const dpp::slashcommand_t&)> execute;
};

#endif