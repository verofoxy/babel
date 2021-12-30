/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** Main.cpp
*/

#include <iostream>

#include "BabelException.hpp"
#include "Server.hpp"

int main()
{
    Babel::Server server(4242);

    try {
        server.loop();
    } catch (const Babel::BabelException &e) {
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        return (84);
    }
    return (0);
}