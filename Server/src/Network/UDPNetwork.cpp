/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** UDPNetwork.cpp
*/

#include <iostream>

#include "UDPNetwork.hpp"
#include "NetworkException.hpp"
#include "Command.hpp"

Babel::UDPNetwork::UDPNetwork(uint16_t port)
    : m_socket(m_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    m_socket.native_non_blocking(true);
}

void Babel::UDPNetwork::receivePacket()
{
    asio::ip::udp::endpoint remoteEndpoint;
    uint8_t headerBuffer[sizeof(PacketHeader)];

    try {
        m_socket.receive_from(asio::buffer(headerBuffer, sizeof(PacketHeader)), remoteEndpoint);

        auto packetHeader = reinterpret_cast<PacketHeader *>(headerBuffer);
        if (packetHeader->magic != BABEL_MAGIC_NUMBER)
            return;

        std::vector<uint8_t> dataBuffer(packetHeader->size);
        m_socket.receive_from(asio::buffer(dataBuffer, packetHeader->size), remoteEndpoint);

        if (clientExists(remoteEndpoint.address().to_string(), remoteEndpoint.port())) {
            Client &client = getClient(remoteEndpoint.address().to_string(), remoteEndpoint.port());
            client.data = dataBuffer;
            Command::executeCommand(*this, packetHeader->type, client);
        } else {
            Client newClient{.data = dataBuffer, .ip = remoteEndpoint.address().to_string(),
                             .port = remoteEndpoint.port()};
            m_clients.emplace_back(newClient);
            Command::executeCommand(*this, packetHeader->type, newClient);
        }

    } catch (const NetworkException &e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
    } catch (const std::system_error &) {}
}

void Babel::UDPNetwork::sendPacket(const std::string &ip, uint16_t port, const PacketHeader &header,
                                   const std::vector<uint8_t> &data)
{
    const auto remoteEndpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(ip), port);

    try {
        m_socket.send_to(asio::buffer(&header, sizeof(header)), remoteEndpoint);
        m_socket.send_to(asio::buffer(data.data(), sizeof(uint8_t) * data.size()), remoteEndpoint);
    } catch (const asio::system_error &e) {
        throw NetworkException("Network", e.what());
    }
}

bool Babel::UDPNetwork::clientExists(const std::string &ip, uint16_t port) const
{
    for (const auto &client : m_clients)
        if (client.ip == ip && client.port == port)
            return (true);
    return (false);
}

Babel::Client &Babel::UDPNetwork::getClient(const std::string &ip, uint16_t port)
{
    for (auto &client : m_clients) {
        if (client.ip == ip && client.port == port)
            return (client);
    }
    throw NetworkException("Network", "Client not found");
}
