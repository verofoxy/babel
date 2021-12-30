/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** UDPNetwork.hpp
*/

#pragma once

#include "asio.hpp"

#include "INetwork.hpp"

namespace Babel {

    struct Client {
        std::string username{};
        std::vector<uint8_t> data{};
        std::string ip{};
        uint16_t port{};
    };

    class UDPNetwork : public INetwork {
    public:
        explicit UDPNetwork(uint16_t port);
        ~UDPNetwork() override = default;

        [[nodiscard]] bool clientExists(const std::string &ip, uint16_t port) const;
        [[nodiscard]] Client &getClient(const std::string &ip, uint16_t port);

        void receivePacket() override;
        void sendPacket(const std::string &ip, uint16_t port, const PacketHeader &header,
                        const std::vector<uint8_t> &data) override;
    private:
        asio::io_context m_ioContext{};
        asio::ip::udp::socket m_socket;
        std::vector<Client> m_clients{};
    };
}