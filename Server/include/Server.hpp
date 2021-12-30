/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** Server.hpp
*/

#pragma once

#include <string>
#include <vector>

#include "asio.hpp"

namespace Babel {
    class Server {
    public:
        explicit Server(uint16_t port);
        ~Server() = default;

        void loop() const;

    private:
        uint16_t m_port;

        static void closeHandler(int signal);
        static bool isCloseRequested(bool close);
    };
}