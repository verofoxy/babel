/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** UDPNetwork.hpp
*/

#pragma once

#include <QUdpSocket>

#include "INetwork.hpp"

#include "PortAudio.hpp"
#include "Opus.hpp"

namespace Babel {
    struct Client {
        std::vector<uint8_t> data;
        std::string ip;
        uint16_t port;
    };

    class UDPNetwork : public INetwork {
    public:
        UDPNetwork(uint16_t port);
        ~UDPNetwork() override = default;

        [[nodiscard]] bool clientExists(const std::string &ip, uint16_t port) const;
        [[nodiscard]] Client &getClient(const std::string &ip, uint16_t port);

        void receivePacket() override;
        void sendPacket(const std::string &ip, uint16_t port, const PacketHeader &header,
                        const std::vector<uint8_t> &data) override;
    private:
        QUdpSocket m_socket{};
        std::vector<Client> m_clients{};

        PortAudio           m_audio{};
        Opus                m_opus{};
    };
}