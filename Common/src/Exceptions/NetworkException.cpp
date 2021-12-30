/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** NetworkException.cpp
*/

#include "NetworkException.hpp"

Babel::NetworkException::NetworkException(const std::string &component, const std::string &message)
    : BabelException(component, message)
{
}
