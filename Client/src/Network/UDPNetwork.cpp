/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** UDPNetwork.cpp
*/

#include "UDPNetwork.hpp"
#include "Command.hpp"
#include "NetworkException.hpp"

Babel::UDPNetwork::UDPNetwork(uint16_t port)
{
    if (port != 0) {
        m_socket.bind(port);
        m_audio.playRecord();
        m_opus.setupDecoder();
    }
}

void Babel::UDPNetwork::receivePacket()
{
    QHostAddress remoteHost;
    quint16 remotePort;
    uint8_t headerBuffer[sizeof(PacketHeader)];

    if (!m_socket.hasPendingDatagrams())
        return;
    m_socket.readDatagram(reinterpret_cast<char *>(headerBuffer), sizeof(PacketHeader), &remoteHost, &remotePort);

    auto packetHeader = reinterpret_cast<PacketHeader *>(headerBuffer);
    if (packetHeader->magic != BABEL_MAGIC_NUMBER)
        return;

    std::vector<uint8_t> dataBuffer(packetHeader->size);
    m_socket.readDatagram(reinterpret_cast<char *>(dataBuffer.data()), static_cast<qint64>(packetHeader->size));

    if (clientExists(remoteHost.toString().toStdString(), remotePort)) {
        Client &client = getClient(remoteHost.toString().toStdString(), remotePort);
        client.data = dataBuffer;
        Command::executeCommand((*this), packetHeader->type, client, m_audio, m_opus);
    } else {
        Client newClient{.data = dataBuffer, .ip = remoteHost.toString().toStdString(), .port = remotePort};
        m_clients.emplace_back(newClient);
        Command::executeCommand((*this), packetHeader->type, newClient, m_audio, m_opus);
    }
    /* std::string str(dataBuffer.begin(), dataBuffer.end());
    std::cout << str << std::endl; */
}

void Babel::UDPNetwork::sendPacket(const std::string &ip, uint16_t port, const PacketHeader &header,
                                   const std::vector<uint8_t> &data)
{
    if (m_socket.writeDatagram(reinterpret_cast<const char *>(&header), sizeof(header), QHostAddress(ip.c_str()),
                               port) < 0)
        throw NetworkException("Network", "Failed to write datagram packet");
    if (m_socket.writeDatagram(reinterpret_cast<const char *>(data.data()), sizeof(uint8_t) * header.size,
                               QHostAddress(ip.c_str()), port) < 0)
        throw NetworkException("Network", "Failed to write datagram packet");
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