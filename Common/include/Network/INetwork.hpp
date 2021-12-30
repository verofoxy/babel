/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** INetwork.hpp
*/

#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace Babel {

    static constexpr int BABEL_MAGIC_NUMBER = 0x5BC3;

    enum PacketType {
        NONE,
        SOUND,
        CALL,
        HANGOUT,
    };

    struct PacketHeader {
        int magic{BABEL_MAGIC_NUMBER};
        PacketType type{NONE};
        std::size_t size{0};
    };

    class INetwork {
    public:
        virtual ~INetwork() = default;

        virtual void receivePacket() = 0;
        virtual void sendPacket(const std::string &ip, uint16_t port, const PacketHeader &header,
                                const std::vector<uint8_t> &data) = 0;
    };
}
