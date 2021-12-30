/*
** EPITECH PROJECT, 2021
** CPP_babel_2021
** File description:
** BabelException.cpp
*/

#include "BabelException.hpp"

Babel::BabelException::BabelException(const std::string &component, const std::string &message)
    : m_component(component), m_message(message)
{
}

const std::string &Babel::BabelException::getComponent() const noexcept
{
    return (m_component);
}

const char *Babel::BabelException::what() const noexcept
{
    return (m_message.c_str());
}
