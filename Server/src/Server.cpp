/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** Server.cpp
*/

#include <csignal>
#include <iostream>

#include "Server.hpp"
#include "UDPNetwork.hpp"

Babel::Server::Server(uint16_t port) : m_port(port)
{
}

void Babel::Server::loop() const
{
    UDPNetwork udp(m_port);

    std::signal(SIGINT, closeHandler);
    std::cout << "Server started. Listening on ::" << m_port << std::endl;
    while (!isCloseRequested(false)) {
        udp.receivePacket();
    }
    std::signal(SIGINT, SIG_DFL);
}

void Babel::Server::closeHandler(int)
{
    isCloseRequested(true);
}

bool Babel::Server::isCloseRequested(bool close)
{
    static bool isClosed = false;

    if (close)
        isClosed = !isClosed;
    return (isClosed);
}
