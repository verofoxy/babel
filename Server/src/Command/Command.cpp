/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** Command.cpp
*/

#include <unordered_map>
#include <iostream>

#include "Command.hpp"

static const std::unordered_map<Babel::PacketType,
                      std::function<void(Babel::INetwork &udp, Babel::Client &client)>> commands =
{
                        {Babel::NONE, Babel::Command::nothing},
                        {Babel::CALL, Babel::Command::call},
                        {Babel::HANGOUT, Babel::Command::hangout},
};

void Babel::Command::executeCommand(INetwork &udp, PacketType type, Client &client)
{
    try {
        commands.at(type)(udp, client);
    } catch (const std::out_of_range &e) {}
}

void Babel::Command::nothing(INetwork &, Client &)
{
    std::cout << "Server: Receive default packet" << std::endl;
}

void Babel::Command::call(INetwork &, Client &client)
{
    std::cout << "Server: Receive call packet" << std::endl;
    std::cout << "Server: " << client.ip << ":" << client.port << " want to call: " << client.data.data() << std::endl;
}

void Babel::Command::hangout(INetwork &, Client &client)
{
    std::cout << "Server: Receive hangout packet" << std::endl;
    std::cout << "Server: " << client.ip << ":" << client.port << " put a term to is call" << std::endl;
}
