/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** Command.hpp
*/

#pragma once

#include "UDPNetwork.hpp"

namespace Babel {
    class Command {
    public:
        Command() = default;
        ~Command() = default;

        static void executeCommand(INetwork &udp, PacketType type, Client &client);
        static void nothing(INetwork &udp, Client &client);
        static void call(INetwork &udp, Client &client);
        static void hangout(INetwork &udp, Client &client);
    };
}