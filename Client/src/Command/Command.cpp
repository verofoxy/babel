/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** Command.cpp
*/

#include <unordered_map>
#include <iostream>
#include <port.h>

#include "Command.hpp"
#include "Opus.hpp"
#include "PortAudio.hpp"

static const std::unordered_map<Babel::PacketType,
                      std::function<void(Babel::INetwork &udp, Babel::Client &client, Babel::PortAudio &audio, Babel::Opus &opus)>> commands =
{
                        { Babel::SOUND, Babel::Command::sound}
};

void Babel::Command::executeCommand(INetwork &udp, PacketType type, Client &client, Babel::PortAudio &audio, Babel::Opus &opus)
{
    try {
        commands.at(type)(udp, client, audio, opus);
    } catch (const std::out_of_range &e) {}
}

void Babel::Command::sound(INetwork &, Client &client, Babel::PortAudio &audio, Babel::Opus &opus)
{
    auto dataSound = Babel::EncodedData{.sample = client.data.data(), .nbBytes= 160};
    opus.decode(dataSound);
    audio.pushSample(opus.getDecodedSound());
}